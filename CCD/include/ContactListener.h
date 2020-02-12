#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#include<Box2D/Box2D.h>



class ContactListener : public b2ContactListener{
public:

   void BeginContact(b2Contact* contact) {

     //only dynamic objects should change color
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

       //only dynamic objects should change color
       auto tipA = contact->GetFixtureA()->GetBody()->GetType();
       auto tipB = contact->GetFixtureB()->GetBody()->GetType();
       if ( tipA == b2_dynamicBody ) {
           static_cast<Shape*>( contact->GetFixtureA()->GetBody()->GetUserData() )->endContact();
       }

       if ( tipB == b2_dynamicBody ) {
            static_cast<Shape*>( contact->GetFixtureB()->GetBody()->GetUserData() )->endContact();
       }
   }




 };

#endif
