////
////  BallHandler.cpp
////  Sample
////
////  Created by Deepak Honakeri on 02/05/20.
////  Copyright © 2020 Deepak Honakeri. All rights reserved.
////
//
//#include "./vector3.cpp"
//#include "../main.cpp"
//
////class to handle ball
//class BallHandler
//{
//    vector3 pos;
//    int cupId;
//
//    public:
//            BallHandler()
//            {
//                pos.x=0.2;
//                pos.y=-1.1;
//                pos.z=0;
//            }
//            //setters
//            void setPosX(float x){
//                    pos.x=x;
//            }
//
//            void setPosY(float y){
//                    pos.y=y;
//            }
//
//            void setPosZ(float z){
//                    pos.z=z;
//            }
//
//            //getters
//            float getPosX(){
//                    return pos.x;
//            }
//            float getPosY(){
//                    return pos.y;
//            }
//            float getPosZ(){
//                    return pos.z;
//            }
//
//            void displayBall()
//            {
//                //reset the cordinate system
//                glLoadIdentity();
//                orientScene();
//
//                // Set material properties and color for ball
//                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorBall);
//                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorBall);
//                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
//                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
//
//                //transalate to proper position
//                glTranslated(pos.x,pos.y,pos.z);
//                glScaled(1,1.3,1);
//
//                //create the sphere
//                glutSolidSphere(0.1, 40.0, 40.0);
//
//            }
//};
