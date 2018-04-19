#!/usr/bin/env python3
# Author: Dr. Robert Heckendorn, Computer Science Department, University of Idaho, 2014
#
# KDTree simple nearest neighbor algorithm expanded to help people understand how it works
#
from math import *
from kdData import *

print(Features)   # a list features
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
    for featureNum in range(0, len(Features)-1) :
        sum = max(sum, abs(a[Features[featureNum]]-b[Features[featureNum]]))
    return sum

def dist3(a, b) :
    sum = 0
    for featureNum in range(0, len(Features)-1) :
        sum += abs(a[Features[featureNum]]-b[Features[featureNum]])**3
    return sum**(1/3)

def dist2(a, b) :
    sum = 0
    for featureNum in range(0, len(Features)-1) :
        sum += (a[Features[featureNum]]-b[Features[featureNum]])**2
    return sqrt(sum)

def dist(a, b) :
    sum = 0
    for featureNum in range(0, len(Features)-1) :
        sum += abs(a[Features[featureNum]]-b[Features[featureNum]])
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
    SortingFeature = Features[featureNum];
    data.sort(key=compare)

    # what is the next featureNum including wrap around
    nextFeatureNum = (featureNum + 1) % len(Features)
    feature = Features[featureNum]

    # check the amount of data in this part of the tree
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

    # if this is a leaf
    if len(kdtree)==2 :   # this is a single node of feature + example
        (feature, example) = kdtree
        return (ourDist(item, example), example)  # return distance and example

    # otherwise if this is a parent
    elif len(kdtree)==3 :
        (feature, example, children) = kdtree   # tree split on feature in example

        # which child do you search?  Which side of the split do you search?
        if item[feature]<=example[feature] :
            # try the lower half
            best = Infinity      # the minimum

            # try first child if it is there
            if 0<len(children) :
                (best, bestex) = nearest(children[0], ourDist, item)
                if abs(item[feature]-example[feature])>best :   # border too far away?  (assumes dist is Euclidean)
                    return (best, bestex)                     # return child as a short cut

            # try parent
            if ourDist(item, example)<best :
                best = ourDist(item, example)
                bestex = example
                if (best == 0) :
                    return (best, bestex)

            # try second child if it is there
            if 1<len(children) :
                (d, e) = nearest(children[1], ourDist, item)
                if d<best :
                    best = d
                    bestex = e
        else :
            # try the upper half
            best = Infinity      # the minimum

            # try second child if it is there
            if 1<len(children) :
                (best, bestex) = nearest(children[1], ourDist, item)
                if abs(item[feature]-example[feature])>best :   # border too far away?  (assumes dist is Euclidean)
                    return (best, bestex)                     # return child as a short cut

            # try parent
            if ourDist(item, example)<best :
                best = ourDist(item, example)
                bestex = example
                if (best == 0) :
                    return (best, bestex)

            # try first child if it is there
            if 0<len(children) :
                (d, e) = nearest(children[0], ourDist, item)
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
    s = 10
    c = {}
    for r in range(0, 256, s) :
        c["R"] = r
        for g in range(0, 256, s) :
            c["G"] = g
            for b in range(0, 256, s) :
                c["B"] = b

                print("TEST:", c)
                ans = nearest(tree, dist2, c)
                ans2 = brute(Data, dist2, c)
                print("ANS1:", ans[0]);
                print(ans[1]);
                print("ANS2:", ans2);
                if (ans2 == ans[1]) : print("SAME")
                else : print("DIFF")
                print()

main()