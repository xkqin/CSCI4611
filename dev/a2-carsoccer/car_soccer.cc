/** CSci-4611 Assignment 2:  Car Soccer
 */

#include "car_soccer.h"
#include "config.h"


CarSoccer::CarSoccer() : GraphicsApp(1024,768, "Car Soccer") {
    // Define a search path for finding data files (images and shaders)
    searchPath_.push_back(".");
    searchPath_.push_back("./data");
    searchPath_.push_back(DATA_DIR_INSTALL);
    searchPath_.push_back(DATA_DIR_BUILD);
    float r = rand() % 50 - 25;
    float w = rand() % 50 - 25;
    car_.set_position(Point3(0,1,45));
    car_.set_velocity(Vector3(0,0,0));
    car_.set_angle(0.0);
    car2.set_position(Point3(0,1,-45));
    car2.set_velocity(Vector3(0,0,0));
    car2.set_angle(0.0);
  //  std::cout << r << std::endl;
    ball_.set_position(Point3(0,2,0));
    ball_.set_velocity(Vector3(r,50,w));
}

CarSoccer::~CarSoccer() {
}


Vector2 CarSoccer::joystick_direction() {
    Vector2 dir(0,0);
    if (IsKeyDown(GLFW_KEY_LEFT))
        dir[0]--;
    if (IsKeyDown(GLFW_KEY_RIGHT))
        dir[0]++;
    if (IsKeyDown(GLFW_KEY_UP))
        dir[1]++;
    if (IsKeyDown(GLFW_KEY_DOWN))
        dir[1]--;
    return dir;
}

Vector2 CarSoccer::joystick_direction2() {
    Vector2 dir(0,0);
    if (IsKeyDown(GLFW_KEY_D))
        dir[0]--;
    if (IsKeyDown(GLFW_KEY_A))
        dir[0]++;
    if (IsKeyDown(GLFW_KEY_S))
        dir[1]++;
    if (IsKeyDown(GLFW_KEY_W))
        dir[1]--;
    return dir;
}


void CarSoccer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
    if (key == GLFW_KEY_SPACE) {
        // Here's where you could call some form of launch_ball();
        float r = rand() % 50 - 25;
        float w = rand() % 50 - 25;
        car_.set_position(Point3(0,1,45));
        car_.set_velocity(Vector3(0,0,0));
        car_.set_angle(0.0);
        car2.set_position(Point3(0,1,-45));
        car2.set_velocity(Vector3(0,0,0));
        car2.set_angle(0.0);
      //  std::cout << r << std::endl;
        ball_.set_position(Point3(0,2,0));
        ball_.set_velocity(Vector3(r,50,w));
    }
}


void CarSoccer::UpdateSimulation(double timeStep) {
    // Here's where you shound do your "simulation", updating the positions of the
    // car and ball as needed and checking for collisions.  Filling this routine
    // in is the main part of the assignment.
    if((ball_.position()[2] <= -50 + ball_.collision_radius() ||
      ball_.position()[2] >= 50 - ball_.collision_radius()) && (
      ball_.position()[0] >= -12 + ball_.collision_radius() &&
      ball_.position()[0] <= 12 - ball_.collision_radius() &&
      ball_.position()[1] <= 10 - ball_.collision_radius())){
        float r = rand() % 50 - 25;
        float w = rand() % 50 - 25;
        car_.set_position(Point3(0,1,45));
        car_.set_velocity(Vector3(0,0,0));
        car_.set_angle(0.0);
        car2.set_position(Point3(0,1,-45));
        car2.set_velocity(Vector3(0,0,0));
        car2.set_angle(0.0);
        //std::cout << r << std::endl;
        ball_.set_position(Point3(0,2,0));
        ball_.set_velocity(Vector3(r,50,w));
      }



      Vector2 dire = joystick_direction();
      if(dire[1] == 0)
      {
        Vector3 move = 5*car_.velocity();
        car_.set_velocity(car_.velocity() - move*timeStep);
        car_.set_position(car_.position() + car_.velocity()*timeStep);
        if(car_.position()[0] > 40 - car_.collision_radius() ||
           car_.position()[0] < -40 + car_.collision_radius() ||
           car_.position()[2] > 50 - car_.collision_radius() ||
           car_.position()[2] < -50 + car_.collision_radius()){
        car_.set_position(car_.position() - car_.velocity() * timeStep);
        car_.set_velocity(Vector3(0,0,0));
      }
      }
      else{
        if(dire.Length() > 0)
        {
          dire = mingfx::Vector2::Normalize(dire);
        }
        if((dire[0] < 0 && dire [1] <0) || (dire[0] > 0 && dire [1] <0) )
        {
            car_.set_angle(car_.angle() + 1*dire[0]*210*timeStep);
        }
        else{  car_.set_angle(car_.angle() - 1*dire[0]*210*timeStep);}
          Vector3 s = 250*(Vector3(-1*dire[1]*sin(car_.angle() * 3.1415926/180),
          0,-dire[1]*cos(car_.angle() *3.1415926/180)));
          Vector3 move = 5*car_.velocity();
          car_.set_velocity(car_.velocity() +  (s-move)*timeStep);
          car_.set_position(car_.position() + car_.velocity()*timeStep);
          if(car_.position()[0] > 40 - car_.collision_radius() ||
             car_.position()[0] < -40 + car_.collision_radius() ||
             car_.position()[2] > 50 - car_.collision_radius() ||
             car_.position()[2] < -50 + car_.collision_radius()){
          car_.set_position(car_.position() - car_.velocity() * timeStep);
          car_.set_velocity(Vector3(0,0,0));
        //  car_.set_angle(car_.angle() - (-dire[0] * 200 * timeStep));
        }


      }

      Vector2 dire2 = joystick_direction2();
      if(dire2[1] == 0)
      {
        Vector3 move = 5*car2.velocity();
        car2.set_velocity(car2.velocity() - move*timeStep);
        car2.set_position(car2.position() + car2.velocity()*timeStep);
        if(car2.position()[0] > 40 - car2.collision_radius() ||
           car2.position()[0] < -40 + car2.collision_radius() ||
           car2.position()[2] > 50 - car2.collision_radius() ||
           car2.position()[2] < -50 + car2.collision_radius()){
        car2.set_position(car2.position() - car2.velocity() * timeStep);
        car2.set_velocity(Vector3(0,0,0));
      }
      }
      else{
        if(dire2.Length() > 0)
        {
          dire2 = mingfx::Vector2::Normalize(dire2);
        }
        if((dire2[0] < 0 && dire2 [1] <0) || (dire2[0] > 0 && dire2 [1] <0) )
        {
            car2.set_angle(car2.angle() + 1*dire2[0]*210*timeStep);
        }
        else{  car2.set_angle(car2.angle() - 1*dire2[0]*210*timeStep);}
          Vector3 s = 270*(Vector3(-1*dire2[1]*sin(car2.angle() * 3.1415926/180),
          0,-dire2[1]*cos(car2.angle() *3.1415926/180)));
          Vector3 move = 5*car2.velocity();
          car2.set_velocity(car2.velocity() +  (s-move)*timeStep);
          car2.set_position(car2.position() + car2.velocity()*timeStep);
          if(car2.position()[0] > 40 - car2.collision_radius() ||
             car2.position()[0] < -40 + car2.collision_radius() ||
             car2.position()[2] > 50 - car2.collision_radius() ||
             car2.position()[2] < -50 + car2.collision_radius()){
          car2.set_position(car2.position() - car2.velocity() * timeStep);
          car2.set_velocity(Vector3(0,0,0));
        //  car_.set_angle(car_.angle() - (-dire[0] * 200 * timeStep));
        }


      }


      if(ball_.position()[0] < -40 + ball_.collision_radius()){

    //    std::cout << "123 :: a" << newv[1] << std::endl;
        ball_.set_velocity(Vector3(fabs(ball_.velocity()[0]),ball_.velocity()[1],ball_.velocity()[2]));
        ball_.set_position(Point3(-40 + ball_.collision_radius(),ball_.position()[1],ball_.position()[2]));
      }

      if(ball_.position()[0] > 40 - ball_.collision_radius()){


        ball_.set_velocity(Vector3(-fabs(ball_.velocity()[0]),ball_.velocity()[1],ball_.velocity()[2]));
        ball_.set_position(Point3(40 - ball_.collision_radius(),ball_.position()[1],ball_.position()[2]));
      }

      if(ball_.position()[1] <  ball_.collision_radius()){

        ball_.set_velocity(Vector3(ball_.velocity()[0],fabs(ball_.velocity()[1]),ball_.velocity()[2]));
        ball_.set_position(Point3(ball_.position()[0],ball_.collision_radius(),ball_.position()[2]));
      }
      if(ball_.position()[1] >  35 - ball_.collision_radius()){


        ball_.set_velocity(Vector3(ball_.velocity()[0],-fabs(ball_.velocity()[1]),ball_.velocity()[2]));
        ball_.set_position(Point3(ball_.position()[0],35 - ball_.collision_radius(),ball_.position()[2]));
      }



      if(ball_.position()[2] < -50 + ball_.collision_radius()){

        ball_.set_velocity(Vector3(ball_.velocity()[0],ball_.velocity()[1],fabs(ball_.velocity()[2])));
        ball_.set_position(Point3(ball_.position()[0],ball_.position()[1],-50 + ball_.collision_radius()));
      }
      if(ball_.position()[2] > 50 - ball_.collision_radius()){
        ball_.set_velocity(Vector3(ball_.velocity()[0],ball_.velocity()[1],-fabs(ball_.velocity()[2])));
        ball_.set_position(Point3(ball_.position()[0],ball_.position()[1],50 - ball_.collision_radius()));
      }

      Vector3 frc = 0.2* ball_.velocity();

      ball_.set_velocity(ball_.velocity()+ (Vector3(0,-100,0) - frc) * timeStep);


      Vector3 con = ball_.position() - car_.position();
      if(con.Length() <= ball_.collision_radius() + car_.collision_radius()){
        ball_.set_position (car_.position()+(ball_.collision_radius() + car_.collision_radius()) *
          Vector3::Normalize(con));
          Vector3 ve = ball_.velocity() - car_.velocity();
          ball_.set_velocity(ball_.velocity() + ve.Length() * Vector3::Normalize(con));
      }

      Vector3 dis = ball_.position() - car2.position();
      if(dis.Length() <= ball_.collision_radius() + car2.collision_radius()){
        ball_.set_position (car2.position()+(ball_.collision_radius() + car2.collision_radius()) *
          Vector3::Normalize(dis));
          Vector3 ve = ball_.velocity() - car2.velocity();
          ball_.set_velocity(ball_.velocity() + ve.Length() * Vector3::Normalize(dis));
      }

      Vector3 card = car_.position() - car2.position();
      if(card.Length() <= car_.collision_radius() + car2.collision_radius()){
        car_.set_position (car2.position()+(car_.collision_radius() + car2.collision_radius()) *
          Vector3::Normalize(card));
          Vector3 ve = car_.velocity() - car2.velocity();
          car_.set_velocity(car_.velocity() + ve.Length() * Vector3::Normalize(card));
          car2.set_velocity(-1*car2.velocity() - ve.Length() * Vector3::Normalize(card));
          //car2.set_angle(-car_.angle());
      }

            ball_.set_position(ball_.position() + ball_.velocity() * timeStep);

}


void CarSoccer::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::Perspective(60, aspect_ratio(), 1, 1000);
    modelMatrix_ = Matrix4::LookAt(Point3(0,60,70), Point3(0,0,10), Vector3(0,1,0));

    // Set a background color for the screen
    glClearColor(0.8,0.8,0.8, 1);

    // Load some image files we'll use
    fieldTex_.InitFromFile(Platform::FindFile("pitch.png", searchPath_));
    crowdTex_.InitFromFile(Platform::FindFile("crowd.png", searchPath_));
}


void CarSoccer::DrawUsingOpenGL() {
    // Draw the crowd as a fullscreen background image
    quickShapes_.DrawFullscreenTexture(Color(1,1,1), crowdTex_);

    // Draw the field with the field texture on it.
    Color col(16.0/255.0, 46.0/255.0, 9.0/255.0);
    Matrix4 M = Matrix4::Translation(Vector3(0,-0.201,0)) * Matrix4::Scale(Vector3(50, 1, 60));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, col);
    M = Matrix4::Translation(Vector3(0,-0.2,0)) * Matrix4::Scale(Vector3(40, 1, 50));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, Color(1,1,1), fieldTex_);

    // Draw the car
    Color carcol(0.8, 0.2, 0.2);
    Matrix4 Mcar =
        Matrix4::Translation(car_.position() - Point3(0,0,0)) *
        Matrix4::Scale(car_.size()) *
        Matrix4::Scale(Vector3(0.5,0.5,0.5))*
        Matrix4::Rotation(Point3(0,0,0),
        Vector3(0,1,0),GfxMath::ToRadians(car_.angle()));
    quickShapes_.DrawCube(modelMatrix_ * Mcar, viewMatrix_, projMatrix_, carcol);


    // Draw the car
    Color carcol2(0, 0, 1);
    Matrix4 Mcar2 =
        Matrix4::Translation(car2.position() - Point3(0,0,0)) *
        Matrix4::Scale(car2.size()) *
        Matrix4::Scale(Vector3(0.5,0.5,0.5))*
        Matrix4::Rotation(Point3(0,0,0),
        Vector3(0,1,0),GfxMath::ToRadians(car2.angle()));
    quickShapes_.DrawCube(modelMatrix_ * Mcar2, viewMatrix_, projMatrix_, carcol2);

    // Draw the ball
    Color ballcol(1,1,1);
    Matrix4 Mball =
        Matrix4::Translation(ball_.position() - Point3(0,0,0)) *
        Matrix4::Scale(Vector3(ball_.radius(), ball_.radius(), ball_.radius()));
    quickShapes_.DrawSphere(modelMatrix_ * Mball, viewMatrix_, projMatrix_, ballcol);


    // Draw the ball's shadow -- this is a bit of a hack, scaling Y by zero
    // flattens the sphere into a pancake, which we then draw just a bit
    // above the ground plane.
    Color shadowcol(0.2,0.4,0.15);
    Matrix4 Mshadow =
        Matrix4::Translation(Vector3(ball_.position()[0], -0.1, ball_.position()[2])) *
        Matrix4::Scale(Vector3(ball_.radius(), 0, ball_.radius())) *
        Matrix4::RotationX(90);
    quickShapes_.DrawSphere(modelMatrix_ * Mshadow, viewMatrix_, projMatrix_, shadowcol);

    std::vector<Point3> strip;
    strip.push_back(Point3(40,0,50));
    strip.push_back(Point3(-40,0,50));
    strip.push_back(Point3(-40,0,-50));
    strip.push_back(Point3(40,0,-50));
    strip.push_back(Point3(40,0,50));



    strip.push_back(Point3(40,35,50));
    strip.push_back(Point3(-40,35,50));
    strip.push_back(Point3(-40,35,-50));
    strip.push_back(Point3(40,35,-50));
    strip.push_back(Point3(40,35,50));

    quickShapes_.DrawLines(modelMatrix_,viewMatrix_,projMatrix_,Color(1,1,1),
          strip,QuickShapes::LinesType::LINE_STRIP,0.3);

    std::vector<Point3> line;
    line.push_back(Point3(-40,0,50));
    line.push_back(Point3(-40,35,50));

    line.push_back(Point3(-40,0,-50));
    line.push_back(Point3(-40,35,-50));

    line.push_back(Point3(40,0,-50));
    line.push_back(Point3(40,35,-50));

    quickShapes_.DrawLines(modelMatrix_,viewMatrix_,projMatrix_,Color(1,1,1),
          line,QuickShapes::LinesType::LINES,0.3);


    for(int i = -10; i<10; i++){
    for(int j = 0; j < 10 ; j++){
    std::vector<Point3> loop;
    loop.push_back(Point3(i,j,-50));
    loop.push_back(Point3(i+1,j,-50));
    loop.push_back(Point3(i+1,j+1,-50));
    loop.push_back(Point3(i,j+1,-50));
    quickShapes_.DrawLines(modelMatrix_,viewMatrix_,projMatrix_,Color(0,0,1),
           loop,QuickShapes::LinesType::LINE_LOOP,0.1);
         }
       }



       for(int i = -10; i<10; i++){
       for(int j = 0; j < 10 ; j++){
       std::vector<Point3> loop;
       loop.push_back(Point3(i,j,50));
       loop.push_back(Point3(i+1,j,50));
       loop.push_back(Point3(i+1,j+1,50));
       loop.push_back(Point3(i,j+1,50));
       quickShapes_.DrawLines(modelMatrix_,viewMatrix_,projMatrix_,Color(1,0,0),
              loop,QuickShapes::LinesType::LINE_LOOP,0.1);
            }
          }
    // You should add drawing the goals and the boundary of the playing area
    // using quickShapes_.DrawLines()
}
