//
//  nn_functions.c
//  NeuralNetwork
//
//  Created by Moky on 16/4/29.
//  Copyright (c) 2016 Slanissue Inc. All rights reserved.
//

#include "nn_functions.h"

nn_value nn_evaluate(nn_dendrite * dendrite)
{
	nn_value value = 0.0f;
	nn_synapse * synapse = dendrite->synapse;
	if (synapse) {
		// 1. evaluate
		value = synapse->activation * dendrite->weight;
		// 2. decline
		synapse->activation *= nn_decay_factor;
	}
	return value;
}

nn_value nn_activation(nn_soma * soma)
{
	nn_value value = 0.0f;
	nn_chain_node * node;
	nn_dendrite * dendrite;
	for (node = soma->dendrites; node; node = node->next) {
		dendrite = node->data;
		value += dendrite->evaluate(dendrite);
	}
	return value;
}

void nn_pulse(nn_axon * axon, nn_value activation)
{
	nn_chain_node * node;
	nn_synapse * synapse;
	for (node = axon->terminals; node; node = node->next) {
		synapse = node->data;
		if (synapse) {
			synapse->activation = activation;
		}
	}
}

void nn_calculate(nn_neuron * neuron)
{
	// 1. activation
	nn_soma * soma = &(neuron->soma);
	nn_nucleus * nucleus = &(soma->nucleus);
	nn_value value = nucleus->activation(soma);
	// 2. pulse
	nn_axon * axon = &(neuron->axon);
	axon->pulse(axon, value);
}
