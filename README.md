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

### Collab Team 3

...
