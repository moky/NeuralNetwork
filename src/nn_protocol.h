//
//  nn_protocol.h
//  NeuralNetwork
//
//  Created by Moky on 16/4/29.
//  Copyright (c) 2016 Slanissue Inc. All rights reserved.
//

#ifndef nn_protocol_h
#define nn_protocol_h

#define nn_decay_factor 0.5f

//
// chain table
//
typedef struct _nn_chain_node {
	void * data;
	struct _nn_chain_node * next;
} nn_chain_node;

typedef float nn_value;

struct _nn_dendrite;
struct _nn_soma;
struct _nn_axon;

typedef nn_value (*nn_dendrite_evaluate)(struct _nn_dendrite * dendrite);

typedef nn_value (*nn_nucleus_activation)(struct _nn_soma * soma);

typedef void (*nn_axon_pulse)(struct _nn_axon * axon, nn_value activation);


// Synapse is connected with a terminal on one neuron's axon,
//                        to a dendrite on another neuron's soma
typedef struct _nn_synapse {
	
	nn_value activation;
	
} nn_synapse;

typedef struct _nn_dendrite {
	
	nn_synapse * synapse; // only dendrite has synapse will be evaluated
	
	nn_value weight;
	
	// evaluate the activation of synapse with dendrite's weight
	nn_dendrite_evaluate evaluate;
	
} nn_dendrite;

typedef struct _nn_axon {
	
	// terminals pointing to synapses
	nn_chain_node * terminals; // output
	
	// pulse to each terminal on axon, with activation
	nn_axon_pulse pulse;
	
} nn_axon;

typedef struct _nn_nucleus {
	
	// evaluate each dendrites on the soma
	nn_nucleus_activation activation;
	
} nn_nucleus;

typedef struct _nn_soma {
	
	nn_chain_node * dendrites; // input
	
	nn_nucleus nucleus; // core in body (private)
	
} nn_soma;

typedef struct _nn_neuron {
	
	nn_soma soma; // body
	
	nn_axon axon; // tail
	
} nn_neuron;

#endif /* nn_protocol_h */
