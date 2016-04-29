//
//  nn_functions.h
//  NeuralNetwork
//
//  Created by Moky on 16/4/29.
//  Copyright (c) 2016 Slanissue Inc. All rights reserved.
//

#ifndef nn_functions_h
#define nn_functions_h

#include "nn_protocol.h"

//
// evaluate function for each dendrite
//
nn_value nn_evaluate(nn_dendrite * dendrite);

//
// activation function for nucleus in soma
//
nn_value nn_activation(nn_soma * soma);

//
// pulse function for axon
//
void nn_pulse(nn_axon * axon, nn_value activation);

#endif /* nn_functions_h */
