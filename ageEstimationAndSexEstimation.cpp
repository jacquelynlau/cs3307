#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "caffe/caffe.hpp"
#include "caffe/util/io.hpp"
#include "caffe/blob.hpp"

using namespace caffe;
using namespace std;

int ageFunction(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale) {

  float loss;
  int age_list[8][2]={{0, 2},{4, 6},{8, 12},{15, 20},{25, 32},{38, 43},{48, 53},{60, 100}};

  try {
    Net<float> net("deploy1.prototxt");
    net.CopyTrainedLayersFrom("age_net.caffemodel");
  }

  loss = 0.0;
	vector<Blob<float>*> results = net.ForwardPrefilled(&loss);
	cout << "Result size: "<< results.size();
  cout << "Blob size: "<< net.input_blobs().size();

  const boost::shared_ptr<Blob<float> >& probLayer = net.blob_by_name("prob");
  const float* probs_out = probLayer->cpu_data();

  for (int i = 0; i < probLayer->num(); i++) {
		cout << "Prob = " << probs_out[i*probLayer->height() + 0];
  }

  return 0;
}

int sexFunction(Mat& img) {

  float loss;
  string gender_list[2]={'Male','Female'};

  try {
    Net<float> net("deploy2.prototxt");
    net.CopyTrainedLayersFrom("gender_net.caffemodel");
  }

  loss = 0.0;
  vector<Blob<float>*> results = net.ForwardPrefilled(&loss);
  cout << "Result size: "<< results.size();
  cout << "Blob size: "<< net.input_blobs().size();

  const boost::shared_ptr<Blob<float> >& probLayer = net.blob_by_name("prob");
  const float* probs_out = probLayer->cpu_data();

  for (int i = 0; i < probLayer->num(); i++) {
		cout << "Prob = " << probs_out[i*probLayer->height() + 0];
  }

  return 0;
}
