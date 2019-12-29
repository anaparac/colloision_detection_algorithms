#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#include<Box2D/Box2D.h>

//struktura za info o kontaktnim tockama
//struct ContactPoint{
//    b2Vec2 position;
//    b2PointState state;
//};

class ContactListener : public b2ContactListener
 {


public:
    int m_pointCount;
    ContactPoint m_points[300];


   //override begin i end contact funkcije kako bi prikazali odgovor na koliziju
   void BeginContact(b2Contact* contact) {

     //provjeri jesu li objekti u kontaktu dinamicki -> samo dinamickima mijenjam boju
     auto tipA = contact->GetFixtureA()->GetBody()->GetType();
     auto tipB = contact->GetFixtureB()->GetBody()->GetType();
     if ( tipA == b2_dynamicBody ) {
         static_cast<Shape*>( contact->GetFixtureA()->GetBody()->GetUserData() )->startContact();
     }

     if ( tipB == b2_dynamicBody ) {
        static_cast<Shape*>( contact->GetFixtureB()->GetBody()->GetUserData() )->startContact();
     }
   }

   void EndContact(b2Contact* contact) {

       //provjeri jesu li objekti u kontaktu dinamicki
       auto tipA = contact->GetFixtureA()->GetBody()->GetType();
       auto tipB = contact->GetFixtureB()->GetBody()->GetType();
       if ( tipA == b2_dynamicBody ) {
           static_cast<Shape*>( contact->GetFixtureA()->GetBody()->GetUserData() )->endContact();
       }

       if ( tipB == b2_dynamicBody ) {
            static_cast<Shape*>( contact->GetFixtureB()->GetBody()->GetUserData() )->endContact();
       }
   }

   void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
//        const b2Manifold* manifold = contact->GetManifold();
//        if(!manifold->pointCount)   return;

//        b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
//        b2GetPointStates(state1, state2, oldManifold, manifold);

//        b2WorldManifold wM;
//        contact->GetWorldManifold(&wM);

//        for(int i = 0; i < manifold->pointCount && m_pointCount < 100; ++i){
//            ContactPoint* cp = m_points + m_pointCount;
//            cp->position = wM.points[i];
//            cp->state = state2[i];
//            ++m_pointCount;
//        }

   }


 };

#endif
