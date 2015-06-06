@@[Home](Home.md) -> [ProjectPlanning](ProjectPlanning.md) -> [TaskBuildAndDeployment](TaskBuildAndDeployment.md)

---


## What ##

**Build**:
  * Place new tag on codebase
  * Design and implement proper tag naming approach
  * Have clean download by the tag
  * Run full build for all binaries in sources
  * Have options to build from mainline or from specific branch
  * Have selected branch as default across all targets
  * Create redistributable package - the only properly named zip file with all related binaries and configurations
  * Design release repository under $/builds
  * Have an option to store package in release repository after build

**Deploy**:
  * Allow to deploy selected package to any local PC directory
  * Have an option to deploy with full replacement, deleting logs, recreating AI database
  * Have an option to deploy with replacing only binaries and configuration files

## How ##