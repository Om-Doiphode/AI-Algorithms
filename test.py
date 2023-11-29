import numpy as np

def utility_one(data, parameters):
    return parameters["beta_01"]+parameters["beta_1"]*data["X1"]+parameters["beta_2"]*data["X2"]

def utility_two(data):
    return parameters["beta_02"]+parameters["beta_1"]*data["X1"]+parameters["beta_2"]*data["X2"]

def utility_three(data):
    return parameters["beta_03"]+parameters["beta_1"]*data["Sero"]+parameters["beta_2"]*data["Sero"]

utilities=[utility_one,utility_two,utility_three]


def calculate_probabilities(parameters, data, utilities):
    num_alternatives=len(utilities)

    

data={
    "X1":[2,3,5,7,1,8,4,5,6,7],
    "X2":[1,5,3,8,2,7,5,9,4,2],
    "Sero":[0,0,0,0,0,0,0,0,0,0]
}
parameters={
    "beta_01":0.1,
    "beta_1":0.5,
    "beta_2":0.5,
    "beta_02":1,
    "beta_03":0
}