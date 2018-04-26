/** CSci-4611 Assignment 3:  Earthquake
 */

#include "quake_app.h"
#include "config.h"

#include <iostream>
#include <sstream>

// Number of seconds in 1 year (approx.)
const int PLAYBACK_WINDOW = 12 * 28 * 24 * 60 * 60;

using namespace std;

QuakeApp::QuakeApp() : GraphicsApp(1280,720, "Earthquake"),
    playback_scale_(15000000.0), debug_mode_(false)
{
    // Define a search path for finding data files (images and earthquake db)
    search_path_.push_back(".");
    search_path_.push_back("./data");
    search_path_.push_back(DATA_DIR_INSTALL);
    search_path_.push_back(DATA_DIR_BUILD);
    
    quake_db_ = EarthquakeDatabase(Platform::FindFile("earthquakes.txt", search_path_));
    current_time_ = quake_db_.earthquake(quake_db_.min_index()).date().ToSeconds();
    rt = 0;

 }


QuakeApp::~QuakeApp() {
}


void QuakeApp::InitNanoGUI() {
    // Setup the GUI window
    nanogui::Window *window = new nanogui::Window(screen(), "Earthquake Controls");
    window->setPosition(Eigen::Vector2i(10, 10));
    window->setSize(Eigen::Vector2i(400,200));
    window->setLayout(new nanogui::GroupLayout());
    
    date_label_ = new nanogui::Label(window, "Current Date: MM/DD/YYYY", "sans-bold");
    
    globe_btn_ = new nanogui::Button(window, "Globe");
    globe_btn_->setCallback(std::bind(&QuakeApp::OnGlobeBtnPressed, this));
    globe_btn_->setTooltip("Toggle between map and globe.");
    
    new nanogui::Label(window, "Playback Speed", "sans-bold");
    
    nanogui::Widget *panel = new nanogui::Widget(window);
    panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                            nanogui::Alignment::Middle, 0, 20));
    
    nanogui::Slider *slider = new nanogui::Slider(panel);
    slider->setValue(0.5f);
    slider->setFixedWidth(120);
    
    speed_box_ = new nanogui::TextBox(panel);
    speed_box_->setFixedSize(Eigen::Vector2i(60, 25));
    speed_box_->setValue("50");
    speed_box_->setUnits("%");
    slider->setCallback(std::bind(&QuakeApp::OnSliderUpdate, this, std::placeholders::_1));
    speed_box_->setFixedSize(Eigen::Vector2i(60,25));
    speed_box_->setFontSize(20);
    speed_box_->setAlignment(nanogui::TextBox::Alignment::Right);
    
    nanogui::Button* debug_btn = new nanogui::Button(window, "Toggle Debug Mode");
    debug_btn->setCallback(std::bind(&QuakeApp::OnDebugBtnPressed, this));
    debug_btn->setTooltip("Toggle displaying mesh triangles and normals (can be slow)");
    
    screen()->performLayout();

}

void QuakeApp::OnLeftMouseDrag(const Point2 &pos, const Vector2 &delta) {
    // Optional: In our demo, we adjust the tilt of the globe here when the
    // mouse is dragged up/down on the screen.
}


void QuakeApp::OnGlobeBtnPressed() {
    // TODO: This is where you can switch between flat earth mode and globe mode
    rt = current_time_;
    if(count % 2 == 0)
    {
    earth_.setP();
    }
    else{
       earth_.setR();
    }
    
    count ++;
}

void QuakeApp::OnDebugBtnPressed() {
    debug_mode_ = !debug_mode_;
}

void QuakeApp::OnSliderUpdate(float value) {
    speed_box_->setValue(std::to_string((int) (value * 100)));
    playback_scale_ = 30000000.0*value;
}


void QuakeApp::UpdateSimulation(double dt)  {
    // Advance the current time and loop back to the start if time is past the last earthquake
    current_time_ += playback_scale_ * dt;
    if (current_time_ > quake_db_.earthquake(quake_db_.max_index()).date().ToSeconds()) {
        current_time_ = quake_db_.earthquake(quake_db_.min_index()).date().ToSeconds();

    }
    if (current_time_ < quake_db_.earthquake(quake_db_.min_index()).date().ToSeconds()) {
        current_time_ = quake_db_.earthquake(quake_db_.max_index()).date().ToSeconds();
    }

    
    Date d(current_time_);
    stringstream s;
    s << "Current date: " << d.month()
        << "/" << d.day()
        << "/" << d.year();
    date_label_->setCaption(s.str());
    if(rt == 0)
    {
        earth_.setL(0.0);
        return;
    }
    
    double trt = -(rt  - current_time_ ) / 10000000;
    qt = trt;

//    if (trt > 1.0)
//    {
//      earth_.setL(1.0);
//                return;
//    }

    
    if(trt >0.0 && trt < 1.0){
        if(count % 2 == 1)
        {
           earth_.setL(trt);
            return;
        }
        else{
//                std::cout <<1-trt<< std::endl;
//            if (1-trt < 0.03)
//            {
//                earth_.setL(0.0);
//                return;
//            }
           earth_.setL(1-trt);
            return;
        }

    }
    
 
    
    
    
    // TODO: Any animation, morphing, rotation of the earth, or other things that should
    // be updated once each frame would go here.
}


void QuakeApp::InitOpenGL() {
    // Set up the camera in a good position to see the entire earth in either mode
    proj_matrix_ = Matrix4::Perspective(60, aspect_ratio(), 0.1, 50);
    view_matrix_ = Matrix4::LookAt(Point3(0,0,3.5), Point3(0,0,0), Vector3(0,1,0));
    glClearColor(0.0, 0.0, 0.0, 1);
    
    // Initialize the earth object
    earth_.Init(search_path_);

    // Initialize the texture used for the background image
    stars_tex_.InitFromFile(Platform::FindFile("iss006e40544.png", search_path_));
}


void QuakeApp::DrawUsingOpenGL() {
    quick_shapes_.DrawFullscreenTexture(Color(1,1,1), stars_tex_);
    
    // You can leave this as the identity matrix and we will have a fine view of
    // the earth.  If you want to add any rotation or other animation of the
    // earth, the model_matrix is where you would apply that.
    Matrix4 model_matrix;
    
    // Draw the earth
    earth_.Draw(model_matrix, view_matrix_, proj_matrix_);
    if (debug_mode_) {
        earth_.DrawDebugInfo(model_matrix, view_matrix_, proj_matrix_);
    }

    
    // TODO: You'll also need to draw the earthquakes.  It's up to you exactly
    // how you wish to do that.
    int start = quake_db_.FindMostRecentQuake(Date (current_time_ - PLAYBACK_WINDOW ));
    int endTime = quake_db_.FindMostRecentQuake(Date(current_time_));
    for (int i = start; i <= endTime ; i++){
        Earthquake ea = quake_db_.earthquake(i);
        Point3 position;
        if(count % 2 == 0){
        position = earth_.LatLongToPlane(ea.latitude(), ea.longitude());
        }
        else{
        position = earth_.LatLongToSphere(ea.latitude(), ea.longitude());
        }
        if(qt >=0.0 && qt <=1.0){
            if(count % 2 == 0)
            {
                position = Point3::Lerp(earth_.LatLongToSphere(ea.latitude(), ea.longitude()),earth_.LatLongToPlane(ea.latitude(), ea.longitude()),qt);
                
            }
            else{
                position = Point3::Lerp(earth_.LatLongToSphere(ea.latitude(), ea.longitude()),earth_.LatLongToPlane(ea.latitude(), ea.longitude()),(1-qt));
            }
        }
                if(rt == 0)
                {
                    position = earth_.LatLongToPlane(ea.latitude(), ea.longitude());
                }

        

        float psize = ea.magnitude() / 200.0;

        float mul_size = (current_time_ - ea.date().ToSeconds()) / (PLAYBACK_WINDOW);
        float size;
        size =psize *( 1.0 - mul_size );

        Color ec(0,0,0);
        if(ea.magnitude() < 6.8)
            ec = Color(0.8,0.8,0.2);
        else ec = Color(0.8,0.2,0.2);
       Matrix4 sphereM = Matrix4::Translation(Vector3(position[0],position[1],position[2]))*Matrix4::Scale(Vector3(size,size,size));
        quick_shapes_.DrawSphere(sphereM, view_matrix_, proj_matrix_, ec);
        
    }

}




