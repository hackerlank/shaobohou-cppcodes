#ifndef SELECTABLE_H
#define SELECTABLE_H


#include <set>
#include <vector>
#include <algorithm>
#include <limits>


// pre-declaration
class SelectableGroup;


// Selectable interface
class Selectable
{
public:
    friend class SelectableGroup;

    Selectable() : m_dim(0) {}
    virtual ~Selectable() {}

    // computes the selection distance of this Selectable object from (x, y)
    virtual int select(int x, int y) = 0;

    // update this Selectable object with values (x, y)
    virtual void update(int x, int y) = 0;

    // register this Selectable object (and optionally its sub-components) with a Selectable group
    virtual void registerCascade(SelectableGroup &selectables) = 0;

    // replace the Selectable pointer selected if the current Selectable is with 
    // a maximum threshold maxDist and is "closer" than selected, an Selectable 
    // is closer if its dimensionality is lower, or if its selection distance is
    // less than bestDist and the dimensionalities are the same.
    void selectIfCloser(int x, int y, Selectable *&selected, int &bestDist, const int maxDist)
    {
        const int currDist =  select(x, y);
        if(currDist <= maxDist)
        {
            if(!selected || m_dim<selected->m_dim || (m_dim==selected->m_dim && currDist<bestDist))
            {
                selected = this;
                bestDist = currDist;
            }
        }
    }

    // update this Selectable object and recursive update its dependant objects
    void updateCascade(int x, int y)
    {
        update(x, y);

        for(std::set<Selectable*>::iterator it = m_parents.begin(); it != m_parents.end(); it++)
        {
            (*it)->updateCascade(x, y);
        }
    }

private:
    int m_dim;
    std::set<Selectable*> m_parents;     // other Selectable objects that depend on this Selectable object

    Selectable(const Selectable &other);
    Selectable& operator=(const Selectable &other);
};


// Selectable Group
class SelectableGroup
{
public:

    // select the lowest dimensional object with a fixed radius around (x, y).
    // if multiple objects of the same dimensionaity are within the radius,
    // then select the nearest one
    Selectable* selectObject(const int x, const int y, const int radius=10)
    {
        Selectable *selected = 0;

        int bestDist = std::numeric_limits<int>::max();
        for(std::set<Selectable*>::iterator it = selectables.begin(); it != selectables.end(); it++)
        {
            (*it)->selectIfCloser(x, y, selected, bestDist, radius*radius);
        }

        return selected;
    }

    // register selectable parent as a dependant of Selectable child
    void registerObject(Selectable *parent, Selectable *child)
    {
        if(parent && child)
        {
            child->m_parents.insert(parent);

            // insert parent if absent
            if(std::find(selectables.begin(), selectables.end(), parent)==selectables.end())
            {
                selectables.insert(parent);
            }

            // insert child if absent
            if(std::find(selectables.begin(), selectables.end(), child)==selectables.end())
            {
                selectables.insert(child);
            }
        }
    }

private:
    std::set<Selectable*> selectables;
};


#endif
