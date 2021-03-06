#ifndef _FEATURE_MATCH_LOCALIZER_H_
#define _FEATURE_MATCH_LOCALIZER_H_

#include "MonocularLocalizer.h"
#include "KeyframeMatch.h"
#include "KeyframeContainer.h"

class FeatureMatchLocalizer : public MonocularLocalizer
{
  struct KeyframePositionSorter
  {
    Eigen::Matrix4f currentPose;
    KeyframePositionSorter(Eigen::Matrix4f pose): currentPose(pose) {};
    
    bool operator()(KeyframeContainer* kfc1, KeyframeContainer* kfc2)
    {
      return (kfc1->GetTf().block<3,1>(0,3)-currentPose.block<3,1>(0,3)).norm() < (kfc2->GetTf().block<3,1>(0,3)-currentPose.block<3,1>(0,3)).norm();
    }
  };

public:

  FeatureMatchLocalizer(const std::vector<CameraContainer*>& train, std::string descriptor_type, bool show_matches = false, bool load_descriptors = false, std::string descriptor_filename = "");
  virtual bool localize(const cv::Mat& img, const cv::Mat& K, Eigen::Matrix4f* pose, Eigen::Matrix4f* pose_guess = NULL);
private:
  std::vector< KeyframeMatch > FindImageMatches(KeyframeContainer* img, int k, Eigen::Matrix4f* pose_guess = NULL, unsigned int search_bound = 0);
  bool WriteDescriptorsToFile(std::string filename);


  std::vector<KeyframeContainer*> keyframes; 
  std::string desc_type;
  bool show_matches;
};

#endif
