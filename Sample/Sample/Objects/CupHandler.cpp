////
////  CupHandler.cpp
////  Sample
////
////  Created by Deepak Honakeri on 02/05/20.
////  Copyright © 2020 Deepak Honakeri. All rights reserved.
////
//
//#include <GLUT/GLUT.h>
//#include "../main.cpp"
//#include "./vector3.cpp"
//
////class to handle Cup
//class CupHandler
//{
//    vector3 pos;
//    int cupRegionId;
//    int switchTransition;
//    public:
//        CupHandler()
//        {
//            pos.x=0;
//            pos.y=0;
//            pos.z=0;
//            switchTransition=1;
//        }
//
//        CupHandler(int x,int y,int z)
//        {
//            pos.x=x;
//            pos.y=y;
//            pos.z=z;
//            switchTransition=1;
//        }
//
//        //setters
//        void setPosX(float x){
//                pos.x=x;
//        }
//
//        void setPosY(float y){
//                pos.y=y;
//        }
//
//        void setPosZ(float z){
//                pos.z=z;
//        }
//
//        //getters
//        float getPosX(){
//                return pos.x;
//        }
//        float getPosY(){
//                return pos.y;
//        }
//        float getPosZ(){
//                return pos.z;
//        }
//
//        void displayCup()
//        {
//
//            //reset the cordinate system
//            glLoadIdentity();
//
//            orientScene();
//
//            // Set material properties and color for ball
//            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorCups);
//            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorCups);
//            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
//            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
//
//
//            //trasalate to proper position
//            glTranslated(pos.x,pos.y,pos.z);
//
//            //creates a frustum
//            GLUquadricObj *quadratic;
//            quadratic = gluNewQuadric();
//
//            // rotate the frustum along y axis
//            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
//            gluCylinder(quadratic,0.2f,0.16f,0.5f,50,50);
//
//
//        }
//
//        //used for ball cover animation (top to down cup movement)
//        void updateYPos()
//        {
//            //decide between top to bottom or bottom to top animation
//            if(switchTransitionFinished!=1)
//            {
//                if(pos.y>-1.2)
//                {
//                    pos.y-=speedToptoDownAnimation;
//                }else
//                {
//                    animationTypeFlag=1;
//                }
//            }
//            else
//            {
//                if(pos.y<0)
//                {
//                    pos.y+=speedToptoDownAnimation;
//                }else
//                {
//                    animationTypeFlag=2;
//                }
//            }
//        }
//
//        int getRegion(){
//            return cupRegionId;
//        }
//
//        void setRegion(int reg){
//            cupRegionId=reg;;
//        }
//
//};
