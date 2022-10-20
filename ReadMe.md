# Human Detection and Tracking

[![Build Status](https://github.com/niteshjha08/Human-Detection-and-Tracking/actions/workflows/build_and_coveralls.yml/badge.svg)](https://github.com/niteshjha08/Human-Detection-and-Tracking/actions/workflows/build_and_coveralls.yml)
[![Coverage Status](https://coveralls.io/repos/github/niteshjha08/Human-Detection-and-Tracking/badge.svg?branch=master)](https://coveralls.io/github/niteshjha08/Human-Detection-and-Tracking?branch=master)

Human detection and tracking module writtern in C++. The module is based on YOLO for object detection and multi-object tracking algorithm to continously track humans in the frame. The co-ordinates of the detections are received in the robot reference frame from the module.

## Project Members
<ul>
    <li>Nitesh Jha (UID - 117525366)</li>
    <li>Tanuj Thakkar (UID - 117817539)</li>
</ul>

## Overview
Real-time obstacle detection is necessary for robot motion in dynamic environments so that the robot has enough time to actively avoid the obstacle.
We propose a module that can detect humans and track their movement, in robot reference frame, over time for this purpose. For the detection, we adopt a deep learning approach and use the YOLOv5 architecture, which is able to detect humans in real time and with high accuracy. Our module can be extended to detect and track any number of classes, although for our application, we only detect the "person" class. The input to the detection module is from a monocular camera. 

The detections are used by the tracking module which distinguishes between entities being tracked using unique identifiers. This module is based on a multi-object tracking algorithm. Tracking is also essential so as to make the overall module reliable in cases when the detection intermittently fails. 

The tracked objects are then transformed to obtain their positions with respect to the world. This information can be used by the robot to avoid obstacles or to execute tasks in their vicinity. 

## Deliverables
<li>A C++ module to detect and track humans with a single RGB camera</li>
<li>UML Diagrams</li>
<li>Developer Documentation of the C++ module with ReadMe</li>
<li>Code-base following Google styling guidelines for C++</li>
<li>Github CI and Coveralls</li>

## Instructions

### Dependencies
```
    sh requirements.sh
```
### Build and Compile
```
    sh build.sh
```

### Running the package
```
    ./build/app/app
```

### Running tests
```
    ./build/test/cpp-test
```

### Running cpplint
```
    sh cpplint.sh
```

### Running cppcheck
```
    sh cppcheck.sh
```

### Generating Doxygen Documentation
```
    cd docs
    doxygen Doxygen
```


## Project Design
<ul>
    <li><a href='https://github.com/tanujthakkar/Human-Detection-and-Tracking/blob/master/UML/revised/UML%20Class%20Diagram.png' >UML Class Diagram</a></li>
    <li><a href='https://github.com/tanujthakkar/Human-Detection-and-Tracking/blob/master/UML/UML%20Activity%20Diagram.png' >UML Activity Diagram</a></li>
    <li><a href='https://github.com/tanujthakkar/Human-Detection-and-Tracking/blob/master/Proposal/Quadchart.png' >Quadchart</a></li>
</ul>

## Project Development
<ul>
    <li>Agile Iterative Process (AIP)</li>
    <ul>
        <li><a href="https://docs.google.com/document/d/1NiZGgrK5uDk6nFAVFyZEgHUmvZiDrnGlzcMZxgvA52M/edit?usp=sharing">Sprint Notes</a></li>
        <li><a href="https://docs.google.com/spreadsheets/d/1RPA_r282Kr-x95LDJrWVvP1dL-oSe8gP9EXjlK-gJtE/edit?usp=sharing">Planning Sheet</a></li>
    </ul>
    <li>Test Driven Development (TDD)</li>
    <ul>
        <li>Phase 1</li>
        <ul>
            <li>Driver: Nitesh Jha</li>
            <li>Navigator: Tanuj Thakkar</li>
        </ul>
    </ul>
    <ul>
        <li>Phase 2</li>
        <ul>
            <li>Driver: Tanuj Thakkar</li>
            <li>Navigator: Nitesh Jha</li>
        </ul>
    </ul>
</ul>

## Additional Links
<ul>
    <li>Proposal</li>
    <ul>
        <li><a href='https://github.com/tanujthakkar/Human-Detection-and-Tracking/blob/master/Proposal/ENPM808X%20-%20Midterm%20Proposal.pdf' >PDF</a></li>
        <li><a href='https://drive.google.com/file/d/1AM1A-1a7mjTDYSgxLombQuMB1ZIcUpeS/view?usp=sharing' >Video</a></li>
    </ul>
    <li>Phase 1</li>
    <ul>
        <li><a href='https://drive.google.com/file/d/1rZQk-GdYQfyh0IcFAtmXDycsm62yBIaS/view?usp=sharing' >Video</a></li>
    </ul>
</ul>
