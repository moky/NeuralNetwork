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
		value = synapse->activation * dendrite->weight;
		synapse->activation *= nn_decay_factor; // decline the synapse's activation
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
