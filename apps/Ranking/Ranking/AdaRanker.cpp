#include "AdaRanker.h"

#include "LinearRegressionRanker.h"

#include <algorithm>
#include <numeric>

void AdaRanker::learn(const QueryData &data)
{
    assert(m_metric != 0);

    weakRankerWeights = std::vector<double>(data.nfeature(), 0.0);
    std::vector<int> weakRankerChecked(data.nfeature(), 0);

    // precompute weak rankers
    std::vector<std::vector<double> > weakRankerScores(data.nquery(), std::vector<double>(data.nfeature(), 0.0));
    for(int q = 0; q < data.nquery(); q++)
    {
        for(int f = 0; f < data.nfeature(); f++)
        {
            weakRankerScores[q][f] = m_metric->measure(weakRank(data.getQuery(q), f));
        }
    }

    std::vector<double> scores(1, m_metric->measure(rank(data)));

    // learn weak rankers
    std::vector<double> queryWeights(data.nquery(), 1.0/data.nquery());
    for(int t = 0; t < data.nfeature(); t++)
    {
        std::vector<double> weightedScores(data.nfeature(), 0);
        for(int f = 0; f < data.nfeature(); f++)
        {
            if(weakRankerChecked[f] == 0)
            {
                for(int q = 0; q < data.nquery(); q++)
                {
                    weightedScores[f] += weakRankerScores[q][f]*queryWeights[q];
                }
            }
        }

        // find best weak ranker
        int bestWR = 0;
        for(int f = 0; f < data.nfeature(); f++)
        {
            if(weightedScores[f] > weightedScores[bestWR])
            {
                bestWR = f;
            }
        }

        // compute alpha
        double num = 0.0;
        double den = 0.0;
        for(int q = 0; q < data.nquery(); q++)
        {
            num += queryWeights[q]*(1.0 + weakRankerScores[q][bestWR]);
            den += queryWeights[q]*(1.0 - weakRankerScores[q][bestWR]);
        }
        double alpha = 0.5*(log(num/den));
        weakRankerWeights[bestWR] = alpha;
        weakRankerChecked[bestWR] = 1;

        // update weights
        double newScore = m_metric->measure(rank(data));
        if((newScore-scores.back()) > 1e-4)
        {
            scores.push_back(newScore);
            std::vector<double> queryProbs;
            for(int q = 0; q < data.nquery(); q++)
            {
                queryProbs.push_back(exp(-m_metric->measure(rank(data.getQuery(q)))));
            }
            double totalQueryProb = std::accumulate(queryProbs.begin(), queryProbs.end(), 0.0);
            for(int q = 0; q < data.nquery(); q++)
            {
                queryWeights[q] = queryProbs[q]/totalQueryProb;
            }
        }
        else
        {
            weakRankerWeights[bestWR] = 0.0;
        }

        const int pah = 0;
    }

    const int bah = 0;
}

RankingList AdaRanker::rank(const QueryData::Query &data) const
{
    std::vector<RankingPair> rankings(data.size());
    for(unsigned int i = 0; i < data.size(); i++)
    {
        rankings[i] = RankingPair(0.0, data[i]);
        for(unsigned int f = 0; f < weakRankerWeights.size(); f++)
        {
            rankings[i].first += data[i]->features(f)*weakRankerWeights[f];
        }
    }

    std::sort(rankings.rbegin(), rankings.rend());

    return rankings;
}

RankingList AdaRanker::weakRank(const QueryData::Query &data, const int f) const
{
    RankingList rankings(data.size());
    for(unsigned int i = 0; i < data.size(); i++)
        rankings[i] = RankingPair(data[i]->features(f), data[i]);

    std::sort(rankings.rbegin(), rankings.rend());

    return rankings;
}