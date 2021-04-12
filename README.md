
MEC-simulator
=====================
## _an ETSI-MEC compliant ns-3 module_

---
### Table of Contents:
1. Project Overview
2. Prerequisites
3. Build and Installation
4. Getting Started
5. Contributors
---

### 1. Project Overview 
Network simulator 3 (ns-3) is a popular open source network simulator, which supports multiple network scenarios, such as LTE.

In order to explore the performance of Multi-Access Edge Computing, ns-3 MEC-simulator module is required. MEC-simulator implements entities (e.g., base stations, MEC Hosts, etc.), interactions, and functionalities (e.g., orchestration of MEC resources, distribution of tasks, etc.) standardized in the context of ETSI-MEC, while supporting multi-cell scenarios with mobile users and different user load generator models.

### 2. Prerequisites
The prerequisite of our project is:
```
ns-3.31
```
The official download url of ns-3.31 is [https://www.nsnam.org/releases/ns-3-31/](https://www.nsnam.org/releases/ns-3-31/).

We only test our project on:
```
Ubuntu 20.04
```

### 3. Build and Installation
After the installation of ns-3.31, replace
```
./<Your workplace>/ns-3-allinone/ns-3.31/contrib
```
with the folder **"contrib"** we offered. Then, extract radio_delay.zip:
```
cd ./<Your workplace>/ns-3-allinone/ns-3.31/contrib/mec-sim/model
unzip radio_delay.zip
rm radio_delay.zip
```
Once the source code has been successfully downloaded, you need to re-build ns-3
```
./waf configure --build-profile=debug --enable-examples --enable-tests
./waf clean
./waf
```

### 4. Getting Started
We offer an **example script** to explore the perfomance of MEC-simulator in a MEC-enabled industrial environment, where Unmanned Aircraft System, Automated Guided Vehicle, Industrial Internet of Things, and mixed reality devices jointly exploit computational capabilities deployed at the network edge.
To run a simple simulation, you can use the following command:
```
./waf --run mec-sim_scenario1
```

### 5. Contributors
    Nicholas Mirizzi - nicholas.mirizzi@poliba.it
    Simona Massari - simona.massari@poliba.it
    Giuseppe Piro - giuseppe.piro@poliba.it


---
© 2021 - TELEMATICS LAB - Politecnico di Bari
