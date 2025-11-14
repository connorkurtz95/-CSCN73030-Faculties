# CSCN73030‑Faculties

*A project by the “Facilities” team*

## Table of Contents

* [Project Overview](#project-overview)
* [Features](#features)
* [Installation & Build](#installation-build)
* [Usage](#usage)
* [Project Structure](#project-structure)
* [Authors](#authors)
* [Collaborations](#collaborations)

## Project Overview

This repository contains the source code for the “Faculties” project for the course **CSCN73030**. The project is developed in C++ with CMake as the build system.
The goal of the project is to design and implement a system to manage faculty-related functionality, such as tracking faculty members, departments, and teaching loads.

## Features

* Core classes and data structures for representing faculty members, departments, and courses
* Functions to add, remove, update, and query faculty records
* Support for CMake-based build and configuration

## Installation & Build

To build this project locally:

1. Clone the repository:

   ```bash
   git clone https://github.com/connorkurtz95/-CSCN73030-Faculties.git
   cd -CSCN73030-Faculties
   ```
2. Create a build directory and run CMake:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. The executable(s) will be in the `build` directory.

## Usage

Run the program using:

```bash
./YourExecutableName [arguments]
```

Replace `YourExecutableName` with the actual binary name. Example:

```bash
./facultyManager --load faculty_data.json --report "dept_summary"
```

## Project Structure

```
/              
├─ CMakeLists.txt     ─ project build configuration
├─ src/               ─ source code files (.cpp/.h)
├─ include/           ─ header files
├─ tests/             ─ unit/integration tests
├─ build/             ─ generated build files & binaries
└─ docs/              ─ documentation and design notes (optional)
```

## Authors

* Connor Kurtz
* Grae‑Watson
* RhysHunt

## Collaborations

### Database

* **Current Configuration:**
  The module is operational. The Database team is developing an API that will be used to access the database. They are using Docker for deployment, and a shared server will be utilized for integration.

* **Impact of Configuration Changes:**
  Any modifications to the database configuration may result in loss of access for the application, causing it to cease functioning. The database would need to be reconfigured to align with the Facilities team’s solution. Ideally, steps for this reconfiguration should be documented in the Database team’s README. Changes made to the Facilities team’s configurations are not expected to impact the Database team.

* **Potential Configuration Changes and Impacts:**
  No changes are anticipated once the API is operational. Consistency in the connection configuration is critical to ensure stable access to the database.

* **Requirements and Dependencies:**

  * Requirement from the Database team: a fully functional database API.
  * Requirement from the Facilities team: none.

### Inventory Management

* **Current Configuration:**
  The Inventory Management module is in its initial baseline (v1.0) and currently supports: - Ingredient tracking - Stock quantity management - Expiry monitoring - Basic reporting and alerts. Future sprint tasks include integration with Facilities data for spoilage detection and equipment-linked alerts.

* **Impact of Configuration Changes:**
  Changes to Inventory configuration may impact: - Integration with Facilities - Parsing of shared data formats - Automated reports - Baseline stability

* **Potential Configuration Changes and Impacts:**
  No changes are anticipated once the API is operational. Consistency in the connection configuration is critical to ensure stable access to the Inventory.

* **Requirements and Dependencies:**

  * Requirement from Inventory Management Team: - Stable data formats from collaborating systems - Advance notice of API changes - Access to test data from Facilities/Database teams - Consistent equipment identifiers 
  * Requirement from the Facilities team: - Maintain reliable inventory tracking - tracking and access to parts for the entertainment machines - make orders for parts

### Transactions
**Current Configuration:**
  The transactions team has made and implemented their module for logging and reporting of transactions that occur, however database related features are done with either pseudocode or theoretical. 

* **Impact of Configuration Changes:**
  CBetween the transaction team and the facilities team, if a configuration is changed on the transaction’s team side that changes modules communicate with each other then that could impact the facilities team. Otherwise, any other configuration changes that the other team makes wouldn’t have a noticeable impact on the overall performance of the facilities team.
  
* **Potential Configuration Changes and Impacts:**
If the facilities team decided to change their operating system, internal software or programming language for whatever reason it wouldn’t affect the transactions team in any meaningful way. Since the modules act relatively independently, there is no worry for requirement changes affecting either team.

* **Requirements and Dependencies:**

  * For the transactions team, their requirements include collecting reports of anyone who would make a transaction, store that information with the database team, and create their own internal reports of transactions. Their additional requirements were to have a functioning budget that cannot be exceeded for the restaurant. The part that overlaps between both teams is that the report generation of the facilities team. This will directly work with the transactions team so they can have accurate records of any transactions that take place.  The facilities team does not have any requirements that need information from the transaction team unless they complete their stretch goal of a restaurant wide budget. In this case the facilities team would need to know the budget amount to not overspend on maintenance tasks.
...
