@@[Home](Home.md) -> [Creatures](Creatures.md) -> [aHumanTarget](aHumanTarget.md)

![http://ahuman.googlecode.com/svn/images/wiki/development/robomouses.jpg](http://ahuman.googlecode.com/svn/images/wiki/development/robomouses.jpg)

---


Full biological high-level model with all nucleus, cortices and related circuits

# Overview #

**Functions:**

  * target verifies mind model from several perspectives
  * target analyzes mind model, calculating derived properties
  * target by command plays specified flow scenario
  * target by command generates wiki pages

**Design:**

  * target executes commands from its topic
  * specific components for all sensory and effectors, not patterned in mind engine
  * target itself does not contain sensors or effectors
  * all regions are stubs and produce stub messages
  * all neurolinks are stubs and affect regions as a whole, not individual neurons

# Mind Model Verification #

**Inputs:**

  * mind.xml with linear list of components grouped by areas, and type definitions
  * hmind.xml with full mind hiearchy, containing:
    * components to be used in mind model and referenced in mind.xml
    * component aggregations
    * component elements

**Mapping rules:**

  * each component is represented in mind element hierarchy
  * each leaf hierarchy element is either component or part of component

**Local connectivity rules:**

  * each component connector is connected by links to other components
  * there are several inputs or several outputs
  * all component connectors are in use
  * sensory and motor components are defined

**Global connectivity rules:**

  * for every sensor output connector there is excitatory path to at least some one motor input
  * for every sensor output connector there is any path to at least some input of the same sensor
  * for every motor output connector there is any path to at least some input of the same motor
  * every component input has any path to some sensor or motor output
  * every component output has any path to some sensor or motor input