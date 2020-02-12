#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#include<Box2D/Box2D.h>

//contact points info
struct ContactPoint{
    b2Vec2 position;
    b2PointState state;
};

class ContactListener : public b2ContactListener
 {


public:
    int m_pointCount;
    ContactPoint m_points[300];



   void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
        const b2Manifold* manifold = contact->GetManifold();
        if(!manifold->pointCount)   return;

        b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
        b2GetPointStates(state1, state2, oldManifold, manifold);

        b2WorldManifold wM;
        contact->GetWorldManifold(&wM);

        for(int i = 0; i < manifold->pointCount && m_pointCount < 100; ++i){
            ContactPoint* cp = m_points + m_pointCount;
            cp->position = wM.points[i];
            cp->state = state2[i];
            ++m_pointCount;
        }

   }


 };

#endif
