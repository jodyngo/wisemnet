// *****************************************************************************************
// Copyright (C) 2017 Juan C. SanMiguel and Andrea Cavallaro
// You may use, distribute and modify this code under the terms of the ACADEMIC PUBLIC
// license (see the attached LICENSE_WISE file).
//
// This file is part of the WiseMnet simulator
//
// Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// Please cite the following reference when publishing results obtained with WiseMnet:
//   J. SanMiguel & A. Cavallaro,
//   "Networked Computer Vision: the importance of a holistic simulator",
//   IEEE Computer, 50(7):35-43, Jul 2017, http://ieeexplore.ieee.org/document/7971873/
// *****************************************************************************************

/**
 * \file WiseMultiCameraPeriodicApp_ReID.h
 * \author Juan C. SanMiguel (2017)
 * \brief Header file for the WiseMultiCameraPeriodicApp_ReID class
 * \version 1.4
 */

#ifndef __WISEMULTICAMERAPERIODICAPP_REID_H__
#define __WISEMULTICAMERAPERIODICAPP_REID_H__

#include <wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h>
#include <wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReIDPacket_m.h>
#include <opencv.hpp>

#define HIST_SIZE 16 //Histogram size for People Descriptors (RGB & GABOR)
#define HOG_HIT_THRESHOLD 0
#define HOG_SCALE 1.05
#define HOG_GROUP_THRESHOLD 2
#define HOG_MIN_SIZE 4
#define HOG_MAX_SIZE 8

/*! \class WiseMultiCameraPeriodicApp_ReID
 *  \brief This class implements a camera network oriented to people reidentification
 *
 *  Description...
 *
 */
class WiseMultiCameraPeriodicApp_ReID : public WiseCameraPeriodicApp
{

private:
    std::ostringstream _win_dets,_win_crop,_win_desc_RGB,_win_desc_GAB,_win_sink;

    //Generic params
    int _dataTypeTX;            //!< 1-full frame 2-blob description 3-both
    int _sinkNode;              //!< server to TX data

    //Detection params
    unsigned int _numDet;                //!< number of detected people in current frame
    cv::HOGDescriptor *_hog;    //!< HOG-based people detector
    std::vector<cv::Mat> _GKernelList; //!< List of kernels for Gabor Features
    bool _extractGabor,_extractRGB;  //!<
    cv::Mat _allDescRGB,_allDescGAB;

    bool _show_internals;
    bool _show_sink;
    bool _use_gt_detections;

protected:
    //Functions to be defined in sub-classes (mandatory)
    void at_timer_fired(int index){};  //!< Response to alarms generated by specific algorithm. To define in superclass (mandatory)
    void at_startup();                 //!< Initialize internal variables. To define in sub-classes for each specific algorithm (mandatory)
    void at_finishSpecific(){};           //!< Release resources. To define in sub-classes for each specific algorithm (mandatory)
    bool at_init();                     //!< Initialize resources based on sampled data. To define in sub-classes for each specific algorithm (mandatory)
    bool at_sample();                   //!< Operations for processing each sample. To define in sub-classes for each specific algorithm (mandatory)
    bool at_end_sample();               //!< Operations after processing each sample. To define in sub-classes for each specific algorithm (mandatory)
    void make_measurements(const std::vector<WiseTargetDetection>&) {} ; //!< Conversion of camera detections into ordered lists of measurements for tracking. To define in sub-classes for each specific algorithm (mandatory)
    bool process_network_message(WiseBaseAppPacket *m); //!< Operations for processing each packet from network. To define in sub-classes for each specific algorithm (mandatory)
    void handleDirectApplicationMessage(WiseBaseAppPacket *); //!< Process a received packet from a direct node-to-node links (to be implemented in superclasses of WiseBaseApp)

    void determineSinkNode();
    void initFeatureExtractorGabor();
    void generateDescriptors(cv::Mat frame,std::vector<cv::Rect> found);
    void sendDescriptors();
    void displayDescBGR(cv::Mat b_hist, cv::Mat g_hist, cv::Mat r_hist, int histSize, const string& winname);
    void displayDescGABOR(cv::Mat g_hist, int histSize, const string& winname);

};

#endif // __WiseCameraPeopleDet_H__
