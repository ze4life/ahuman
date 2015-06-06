@@[Home](Home.md) -> [DevelopmentCycle](DevelopmentCycle.md)

![http://ahuman.googlecode.com/svn/images/wiki/procedures/devgirl.jpg](http://ahuman.googlecode.com/svn/images/wiki/procedures/devgirl.jpg)

---


## Development ##

  * The development is a primary part of this Project because its goal is to create practically functioning application that never was created before
  * This development any case will take several years and to ensure certain progress, systematic approach to development is required to be sure that spent efforts are not for stovepipes
  * The Project has 3 major milestones:
    * Ability to fulfill primary function, at least by design
    * Ability to establish UAT for the creature where it could be evaluated
    * Ability to start PROD version - in fact the birthday of the creature
  * The Project goes to these milestones by several phases, where all phases have the same pattern - see below

## Development phase ##

  * Phases are aligned with quarters - so we have first project phases: 2009Q2 - to the end of June, 2009Q3 - to the end of September, 2009Q4 - to the end of year
  * Phase ends with a release no matter how many changes we have
  * Release collects all the changes done during phase and should be stable - so we need regular stabilisation activities near the end of the phase
  * Each new release should be better than previous - more functional and not less stable

## Development Phase Cycle ##

  * Milestone 1: **Planning Freeze**
    * Major criteria: list of tasks to be included in the release is finalised
    * Task list is available as separate sub-project named **Phase-YYYYQY**
    * This milestone occurs one week after the previous phase release
    * By this time new branch is created in **$/branches** as a copy of mainline (trunk) - to support the released code - see Weekly Releases. The development coding is always performed in the mainline

  * Milestone 2: **Development Freeze**
    * Major criteria: all the development tasks are done but can be unstable
    * The development coding is always performed in the **$/sources** (mainline).
    * All the tasks are marked as 100% done. This does not mean that no activity is related to the task - actually adjustments are performed all the time before the release. It means that all the planned code is created and task owner adjusted requirements so that they reflect what is implemented - plans are constantly changing, it is usual.
    * Most reasonable time for this milestone is 2 months after planning
    * Any task not done by the deadline should be reduced
    * Any task that is cannot be done even in reduced state, is descoped from the release
    * The code related to the reduced or descoped tasks, can be stored in **$/research** folder under appropriate name, Research pages should be update this case - see [Research Cycle](ResearchCycle.md)

  * Milestone 3: **Code Freeze**
    * Major criteria: we have a stable version
    * Stable means nobody in the team knows about issues that should be resolved before the release. New forum discussion topic will be started to reveal that fact.
    * The Code Freeze should occur 1 week before release to have a time to prepare package (upgrade UAT or PROD when we have it)

  * Milestone 4: **Release**
    * Major criteria: we made a quarterly release
    * Whenever we have live knowledge base, the release for Human project is something more than just new code. This new code is expected to lead to the planned changes in the knowledge base - and release is ended when we see that these changes occurred and total state of creature is better than was before. If it occurred, we rollback the change.
    * New branch **releaseYYYYqQ** is created in **$/branches** as a copy of mainline (trunk) - to support the released code - see Weekly Releases.
    * Initial state of the branch is tagged in **$/tags**

## Weekly Releases ##

  * If something is occurred that requires to make mandatory update of the release done, exceptional patching schema initiated - each weekend we can make a new release
  * Coding for weekly releases is being performed using branch in **$/branches**
  * Each prepared weekly release is tagged in **$/tags**
  * Changes done in branch should be merged in mainline if applicable
  * If we have UAT or PROD - carefully patch it