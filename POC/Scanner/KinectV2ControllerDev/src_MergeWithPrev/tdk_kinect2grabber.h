#ifndef TDK_KINECT2GRABBER_H
#define TDK_KINECT2GRABBER_H
#include "kinect2_grabber.h"
#include <pcl/visualization/image_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZRGB PointType;

class TDK_Kinect2Grabber
{
public:

    //default constructor for the TDK_Kinect2Grabber class
    TDK_Kinect2Grabber();
    ~TDK_Kinect2Grabber() {}

    //returns true if a new frame is available
    //bool hasFrame();

    void mf_closeKinect();

    //You will change the address pointed by cloud, but if you dont pass by reference,
    //the pointer will not be updated in the calling code, it will point to the same dir.
    //fills the address of assigned cloud-pointer with a XYZRGB point cloud
    void mf_getPointCloudFrame(pcl::PointCloud<PointType>::Ptr &cloud);


    // Gives you frame in im
    // void getRGBFrame(ImageType &im)

    // stores the reference to the qt widget that will be updated from the callback function for
    // RGBframe from grabber
    // setRGBWidget(...);

    // Same for depth image
    // setDepthDisplay(...);

    void mf_SetScanBoxLimits(int x_min,int x_max,int y_min,int y_max,int z_min,int z_max);

private:
    //mutex
    boost::mutex mv_mutex;
    boost::shared_ptr<pcl::Kinect2Grabber> mv_grabber;

    //point cloud
    pcl::PointCloud<PointType>::Ptr mv_cloud;

    //TDK image viewer
    pcl::visualization::ImageViewer::Ptr mv_imageViewer;

    //PSP
    //TDK pcl cloud viewer
    //pcl::visualization::PCLVisualizer::Ptr mv_cloudViewer;

    //call-back updates a member variable with a new point cloud when available
    //          also projects/throws the cloud into the display window
    boost::function<void( const pcl::PointCloud<PointType>::ConstPtr& )> mv_pointCloudCallback =
            [this]( const pcl::PointCloud<PointType>::ConstPtr& ptr ){
        boost::mutex::scoped_lock lock(mv_mutex );

        /* Point Cloud Processing */
        mv_cloud = ptr->makeShared();
    //PSP
        //mv_imageViewer->addRGBImage<PointType>(mv_cloud, "rgb", 1.0 );
        //mv_cloudViewer->addPointCloud<PointType>(mv_cloud, "cloud", 0);
    };

    //bool displayRGBSet;
    //Widget wRGB;
    //bool displayDepthSet;


};

#endif // TDK_KINECT2GRABBER_H
