#!/usr/bin/env python3
# Author: Dr. Robert Heckendorn, Computer Science Department, University of Idaho
#  Version 2: Apr 19, 2018
#
# KDTree simple nearest neighbor algorithm expanded to help people understand how it works
# Version 2:
#   a) some names changed to better explain their purpose
#   b) a formal calling prototype more like my C++ code to clarify that best and bestex
#        behave more like globals and get better throughout the execution as explained in
#        class.
#   c) a bug fix that improves performance.   The code worked before but not quite as
#        intended.  In making the first explanatory copy I left a test out in the leaf node
#        See comment in leaf.
#
from math import *
from kdData2 import *

print(FeaturesList)   # a list features
print(Data)       # a list of dictionaries.  One dictionary for each data sample.

# GLOBALS
#  SortingFeature - what feature to sort on
Infinity = 1E+100   # bigger than maximum distance

def compare(dict) :
    global SortingFeature
    return dict[SortingFeature]


# DISTANCE MEASURES
#
# This assumes that dist(a, b) >= abs(a[f]-b[f])  for all features f

def distMax(a, b) :
    sum = 0
    for featureNum in range(0, len(FeaturesList)-1) :
        sum = max(sum, abs(a[FeaturesList[featureNum]]-b[FeaturesList[featureNum]]))
    return sum

def dist3(a, b) :
    sum = 0
    for featureNum in range(0, len(FeaturesList)-1) :
        sum += abs(a[FeaturesList[featureNum]]-b[FeaturesList[featureNum]])**3
    return sum**(1/3)

def dist2(a, b) :
    sum = 0
    for featureNum in range(0, len(FeaturesList)-1) :
        sum += (a[FeaturesList[featureNum]]-b[FeaturesList[featureNum]])**2
    return sqrt(sum)

def dist(a, b) :
    sum = 0
    for featureNum in range(0, len(FeaturesList)-1) :
        sum += abs(a[FeaturesList[featureNum]]-b[FeaturesList[featureNum]])
    return sum


# BUILD KDTREE
#
# featureNum is the number of the feature in the variable Features
# feature is the feature *name* itself like R, G, or B
#
# PARENT node is: [feature, value, [child1, child2]]
#             or: [feature, value, [child1]]
# LEAF node is: [feature, value]
#
def kdBuild(featureNum, data) :
    global SortingFeature

    # sort on feature number featureNum
    SortingFeature = FeaturesList[featureNum]    # set up the feature to sort on (see compare function)
    data.sort(key=compare)

    # what is the next featureNum including wrap around
    feature = FeaturesList[featureNum]

    # check the amount of data in this part of the tree
    nextFeatureNum = (featureNum + 1) % (len(FeaturesList) - 1)  # don't include Ans feature

    length = len(data)
    # if only 1 then make it a leaf
    if length==1 :
        return [feature, data[0]]
    # if only 2 then make it parent and leaf
    elif length==2 :       # len(childlist) == 1  i.e. single child
        return [feature, data[1], [[nextFeatureNum, data[0]]]]
    # split at *median* of the data in this part of tree and build tree recursively
    else :                 # len(childlist) == 2  i.e. double child
        return [feature,
                data[length//2],
                [kdBuild(nextFeatureNum, data[:length//2-1+1]),
                 kdBuild(nextFeatureNum, data[length//2+1:])]
               ]


# using the given kdtree find the item that is closest to item
def nearest(kdtree, ourDist, item) :
    (best, bestex) = nearestAux(kdtree, ourDist, item, Infinity, None)
    return bestex

# best and bestex are passed in and returned as values of the function.
# In a C++ version kdtre would be the kdtree Matrix, and best and bestex
# could be passed as references as I did in my C++ code making them more like
# globals.   This was not done neatly when I first translated the code to
# my first explanatory version.
def nearestAux(kdtree, ourDist, item, best, bestex) :

    # if this is a leaf
    if len(kdtree)==2 :   # this is a single node of feature + example
        (feature, splitPt) = kdtree
        if ourDist(item, splitPt)<best :     # since passing in best, test if this pt is better!
            print("BESTLEAF:", ourDist(item, splitPt), splitPt)
            return (ourDist(item, splitPt), splitPt)  # return distance and example
        else : 
            return (best, bestex)

    # otherwise if this is a parent
    elif len(kdtree)==3 :
        (feature, splitPt, children) = kdtree   # tree split on feature in example

        # which child do you search?  Which side of the split do you search?
        if item[feature]<=splitPt[feature] :
            # try the LOWER HALF

            # try first child if it is there
            if 0<len(children) :
                (best, bestex) = nearestAux(children[0], ourDist, item, best, bestex)
                if abs(item[feature]-splitPt[feature])>best :   # border too far away?  (assume Euclidean dist)
                    return (best, bestex)             # SHORT CUT

            # try parent
            if ourDist(item, splitPt)<best :
                best = ourDist(item, splitPt)
                bestex = splitPt
                print("BESTPARENT1:", ourDist(item, splitPt), splitPt)
                if (best == 0) :
                    return (best, bestex)

            # try second child if it is there
            if 1<len(children) :
                (d, e) = nearestAux(children[1], ourDist, item, best, bestex)
                if d<best :
                    best = d
                    bestex = e
        else :
            # try the UPPER HALF

            # try second child if it is there
            if 1<len(children) :
                (best, bestex) = nearestAux(children[1], ourDist, item, best, bestex)
                if abs(item[feature]-splitPt[feature])>best :   # border too far away?  (assume Euclidean dist)
                    return (best, bestex)             # SHORT CUT

            # try parent
            if ourDist(item, splitPt)<best :
                best = ourDist(item, splitPt)
                bestex = splitPt
                print("BESTPARENT2:", ourDist(item, splitPt), splitPt)
                if (best == 0) :
                    return (best, bestex)

            # try first child if it is there
            if 0<len(children) :
                (d, e) = nearestAux(children[0], ourDist, item, best, bestex)
                if d<best :
                    best = d
                    bestex = e
 
        return (best, bestex)
    else :
        print("ERROR(nearest): should never get here length of top list of kdtree is", len(kdtree))
        quit(1)


def brute(data, ourDist, c) :
    min = Infinity
    for i in data :
        x = ourDist(i, c)
        if x<min :
            min = x
            guess = i
    return guess


def main() :
    global count
    Test = Data
    tree = kdBuild(0, Data)

    count = 0
    s = 31
    c = {}
    for r in range(0, 256, s) :
        c["R"] = r
        for g in range(0, 256, s) :
            c["G"] = g
            for b in range(0, 256, s) :
                c["B"] = b

                print("SOLVE:", c)
                ans = nearest(tree, dist2, c)
                ans2 = brute(Data, dist2, c)
                print("ANS1:", ans);
                print("ANS2:", ans2);
                if (ans2 == ans) : print("SAME")
                else : print("DIFF")
                print()

main()