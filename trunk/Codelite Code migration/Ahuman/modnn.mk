##
## Auto Generated makefile, please do not edit
##
ProjectName:=modnn

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./aiengine/Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "E:\Personal\ahuman\Codelite Code migration\Ahuman"
ProjectPath            := "E:\Personal\ahuman\Codelite Code migration\Ahuman"
CurrentFileName        :=
CurrentFulePath        :=
CurrentFileFullPath    :=
User                   :=mti00132
Date                   :=12/23/09
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
OutputFile             :=./lib/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            := "$(IncludeSwitch)." "$(IncludeSwitch)./aiengine/include" "$(IncludeSwitch)./aiengine/src/include" "$(IncludeSwitch)./generic/include" "$(IncludeSwitch)./generic/include/stacktrace"  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)./aiengine/include" "$(IncludeSwitch)./aiengine/src/include" "$(IncludeSwitch)./generic/include" "$(IncludeSwitch)./generic/include/stacktrace" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/nn$(ObjectSuffix) $(IntermediateDirectory)/nnactivationfunction$(ObjectSuffix) $(IntermediateDirectory)/nnerrorfunction$(ObjectSuffix) $(IntermediateDirectory)/nnfinder$(ObjectSuffix) $(IntermediateDirectory)/nnfinderfactory$(ObjectSuffix) $(IntermediateDirectory)/nnfinderfactorysample$(ObjectSuffix) $(IntermediateDirectory)/nninductionfunction$(ObjectSuffix) $(IntermediateDirectory)/nnlayer$(ObjectSuffix) $(IntermediateDirectory)/nnlib$(ObjectSuffix) $(IntermediateDirectory)/nnlibdebug$(ObjectSuffix) \
	$(IntermediateDirectory)/nnneuron$(ObjectSuffix) $(IntermediateDirectory)/nnregression$(ObjectSuffix) $(IntermediateDirectory)/nnregressionfactory$(ObjectSuffix) $(IntermediateDirectory)/nnsample$(ObjectSuffix) $(IntermediateDirectory)/nnsamples$(ObjectSuffix) $(IntermediateDirectory)/nnscanpoint$(ObjectSuffix) $(IntermediateDirectory)/nnstopfunction$(ObjectSuffix) $(IntermediateDirectory)/nnstrategy$(ObjectSuffix) $(IntermediateDirectory)/nnstrategybackpropagation$(ObjectSuffix) $(IntermediateDirectory)/nnstrategyhelper$(ObjectSuffix) \
	$(IntermediateDirectory)/nnstrategyscan$(ObjectSuffix) $(IntermediateDirectory)/nnstrategyscaniteration$(ObjectSuffix) $(IntermediateDirectory)/nnvalidatefunction$(ObjectSuffix) $(IntermediateDirectory)/nnvariable$(ObjectSuffix) $(IntermediateDirectory)/nnvariablecategory$(ObjectSuffix) $(IntermediateDirectory)/nnvariables$(ObjectSuffix) $(IntermediateDirectory)/nnvariablescontainer$(ObjectSuffix) $(IntermediateDirectory)/nnvariablesimple$(ObjectSuffix) $(IntermediateDirectory)/nnweights$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@makedir $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

./aiengine/Debug:
	@makedir "./aiengine/Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/nn$(ObjectSuffix): aiengine/src/modnnlib/nn.cpp $(IntermediateDirectory)/nn$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nn.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nn$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nn$(DependSuffix): aiengine/src/modnnlib/nn.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nn$(ObjectSuffix) -MF$(IntermediateDirectory)/nn$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nn.cpp"

$(IntermediateDirectory)/nnactivationfunction$(ObjectSuffix): aiengine/src/modnnlib/nnactivationfunction.cpp $(IntermediateDirectory)/nnactivationfunction$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnactivationfunction.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnactivationfunction$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnactivationfunction$(DependSuffix): aiengine/src/modnnlib/nnactivationfunction.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnactivationfunction$(ObjectSuffix) -MF$(IntermediateDirectory)/nnactivationfunction$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnactivationfunction.cpp"

$(IntermediateDirectory)/nnerrorfunction$(ObjectSuffix): aiengine/src/modnnlib/nnerrorfunction.cpp $(IntermediateDirectory)/nnerrorfunction$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnerrorfunction.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnerrorfunction$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnerrorfunction$(DependSuffix): aiengine/src/modnnlib/nnerrorfunction.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnerrorfunction$(ObjectSuffix) -MF$(IntermediateDirectory)/nnerrorfunction$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnerrorfunction.cpp"

$(IntermediateDirectory)/nnfinder$(ObjectSuffix): aiengine/src/modnnlib/nnfinder.cpp $(IntermediateDirectory)/nnfinder$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnfinder.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnfinder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnfinder$(DependSuffix): aiengine/src/modnnlib/nnfinder.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnfinder$(ObjectSuffix) -MF$(IntermediateDirectory)/nnfinder$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnfinder.cpp"

$(IntermediateDirectory)/nnfinderfactory$(ObjectSuffix): aiengine/src/modnnlib/nnfinderfactory.cpp $(IntermediateDirectory)/nnfinderfactory$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnfinderfactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnfinderfactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnfinderfactory$(DependSuffix): aiengine/src/modnnlib/nnfinderfactory.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnfinderfactory$(ObjectSuffix) -MF$(IntermediateDirectory)/nnfinderfactory$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnfinderfactory.cpp"

$(IntermediateDirectory)/nnfinderfactorysample$(ObjectSuffix): aiengine/src/modnnlib/nnfinderfactorysample.cpp $(IntermediateDirectory)/nnfinderfactorysample$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnfinderfactorysample.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnfinderfactorysample$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnfinderfactorysample$(DependSuffix): aiengine/src/modnnlib/nnfinderfactorysample.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnfinderfactorysample$(ObjectSuffix) -MF$(IntermediateDirectory)/nnfinderfactorysample$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnfinderfactorysample.cpp"

$(IntermediateDirectory)/nninductionfunction$(ObjectSuffix): aiengine/src/modnnlib/nninductionfunction.cpp $(IntermediateDirectory)/nninductionfunction$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nninductionfunction.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nninductionfunction$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nninductionfunction$(DependSuffix): aiengine/src/modnnlib/nninductionfunction.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nninductionfunction$(ObjectSuffix) -MF$(IntermediateDirectory)/nninductionfunction$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nninductionfunction.cpp"

$(IntermediateDirectory)/nnlayer$(ObjectSuffix): aiengine/src/modnnlib/nnlayer.cpp $(IntermediateDirectory)/nnlayer$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnlayer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnlayer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnlayer$(DependSuffix): aiengine/src/modnnlib/nnlayer.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnlayer$(ObjectSuffix) -MF$(IntermediateDirectory)/nnlayer$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnlayer.cpp"

$(IntermediateDirectory)/nnlib$(ObjectSuffix): aiengine/src/modnnlib/nnlib.cpp $(IntermediateDirectory)/nnlib$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnlib.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnlib$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnlib$(DependSuffix): aiengine/src/modnnlib/nnlib.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnlib$(ObjectSuffix) -MF$(IntermediateDirectory)/nnlib$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnlib.cpp"

$(IntermediateDirectory)/nnlibdebug$(ObjectSuffix): aiengine/src/modnnlib/nnlibdebug.cpp $(IntermediateDirectory)/nnlibdebug$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnlibdebug.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnlibdebug$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnlibdebug$(DependSuffix): aiengine/src/modnnlib/nnlibdebug.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnlibdebug$(ObjectSuffix) -MF$(IntermediateDirectory)/nnlibdebug$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnlibdebug.cpp"

$(IntermediateDirectory)/nnneuron$(ObjectSuffix): aiengine/src/modnnlib/nnneuron.cpp $(IntermediateDirectory)/nnneuron$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnneuron.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnneuron$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnneuron$(DependSuffix): aiengine/src/modnnlib/nnneuron.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnneuron$(ObjectSuffix) -MF$(IntermediateDirectory)/nnneuron$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnneuron.cpp"

$(IntermediateDirectory)/nnregression$(ObjectSuffix): aiengine/src/modnnlib/nnregression.cpp $(IntermediateDirectory)/nnregression$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnregression.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnregression$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnregression$(DependSuffix): aiengine/src/modnnlib/nnregression.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnregression$(ObjectSuffix) -MF$(IntermediateDirectory)/nnregression$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnregression.cpp"

$(IntermediateDirectory)/nnregressionfactory$(ObjectSuffix): aiengine/src/modnnlib/nnregressionfactory.cpp $(IntermediateDirectory)/nnregressionfactory$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnregressionfactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnregressionfactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnregressionfactory$(DependSuffix): aiengine/src/modnnlib/nnregressionfactory.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnregressionfactory$(ObjectSuffix) -MF$(IntermediateDirectory)/nnregressionfactory$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnregressionfactory.cpp"

$(IntermediateDirectory)/nnsample$(ObjectSuffix): aiengine/src/modnnlib/nnsample.cpp $(IntermediateDirectory)/nnsample$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnsample.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnsample$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnsample$(DependSuffix): aiengine/src/modnnlib/nnsample.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnsample$(ObjectSuffix) -MF$(IntermediateDirectory)/nnsample$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnsample.cpp"

$(IntermediateDirectory)/nnsamples$(ObjectSuffix): aiengine/src/modnnlib/nnsamples.cpp $(IntermediateDirectory)/nnsamples$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnsamples.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnsamples$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnsamples$(DependSuffix): aiengine/src/modnnlib/nnsamples.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnsamples$(ObjectSuffix) -MF$(IntermediateDirectory)/nnsamples$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnsamples.cpp"

$(IntermediateDirectory)/nnscanpoint$(ObjectSuffix): aiengine/src/modnnlib/nnscanpoint.cpp $(IntermediateDirectory)/nnscanpoint$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnscanpoint.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnscanpoint$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnscanpoint$(DependSuffix): aiengine/src/modnnlib/nnscanpoint.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnscanpoint$(ObjectSuffix) -MF$(IntermediateDirectory)/nnscanpoint$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnscanpoint.cpp"

$(IntermediateDirectory)/nnstopfunction$(ObjectSuffix): aiengine/src/modnnlib/nnstopfunction.cpp $(IntermediateDirectory)/nnstopfunction$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstopfunction.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnstopfunction$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnstopfunction$(DependSuffix): aiengine/src/modnnlib/nnstopfunction.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnstopfunction$(ObjectSuffix) -MF$(IntermediateDirectory)/nnstopfunction$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstopfunction.cpp"

$(IntermediateDirectory)/nnstrategy$(ObjectSuffix): aiengine/src/modnnlib/nnstrategy.cpp $(IntermediateDirectory)/nnstrategy$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategy.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnstrategy$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnstrategy$(DependSuffix): aiengine/src/modnnlib/nnstrategy.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnstrategy$(ObjectSuffix) -MF$(IntermediateDirectory)/nnstrategy$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategy.cpp"

$(IntermediateDirectory)/nnstrategybackpropagation$(ObjectSuffix): aiengine/src/modnnlib/nnstrategybackpropagation.cpp $(IntermediateDirectory)/nnstrategybackpropagation$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategybackpropagation.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnstrategybackpropagation$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnstrategybackpropagation$(DependSuffix): aiengine/src/modnnlib/nnstrategybackpropagation.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnstrategybackpropagation$(ObjectSuffix) -MF$(IntermediateDirectory)/nnstrategybackpropagation$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategybackpropagation.cpp"

$(IntermediateDirectory)/nnstrategyhelper$(ObjectSuffix): aiengine/src/modnnlib/nnstrategyhelper.cpp $(IntermediateDirectory)/nnstrategyhelper$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategyhelper.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnstrategyhelper$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnstrategyhelper$(DependSuffix): aiengine/src/modnnlib/nnstrategyhelper.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnstrategyhelper$(ObjectSuffix) -MF$(IntermediateDirectory)/nnstrategyhelper$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategyhelper.cpp"

$(IntermediateDirectory)/nnstrategyscan$(ObjectSuffix): aiengine/src/modnnlib/nnstrategyscan.cpp $(IntermediateDirectory)/nnstrategyscan$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategyscan.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnstrategyscan$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnstrategyscan$(DependSuffix): aiengine/src/modnnlib/nnstrategyscan.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnstrategyscan$(ObjectSuffix) -MF$(IntermediateDirectory)/nnstrategyscan$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategyscan.cpp"

$(IntermediateDirectory)/nnstrategyscaniteration$(ObjectSuffix): aiengine/src/modnnlib/nnstrategyscaniteration.cpp $(IntermediateDirectory)/nnstrategyscaniteration$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategyscaniteration.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnstrategyscaniteration$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnstrategyscaniteration$(DependSuffix): aiengine/src/modnnlib/nnstrategyscaniteration.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnstrategyscaniteration$(ObjectSuffix) -MF$(IntermediateDirectory)/nnstrategyscaniteration$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnstrategyscaniteration.cpp"

$(IntermediateDirectory)/nnvalidatefunction$(ObjectSuffix): aiengine/src/modnnlib/nnvalidatefunction.cpp $(IntermediateDirectory)/nnvalidatefunction$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvalidatefunction.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnvalidatefunction$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnvalidatefunction$(DependSuffix): aiengine/src/modnnlib/nnvalidatefunction.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnvalidatefunction$(ObjectSuffix) -MF$(IntermediateDirectory)/nnvalidatefunction$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvalidatefunction.cpp"

$(IntermediateDirectory)/nnvariable$(ObjectSuffix): aiengine/src/modnnlib/nnvariable.cpp $(IntermediateDirectory)/nnvariable$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariable.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnvariable$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnvariable$(DependSuffix): aiengine/src/modnnlib/nnvariable.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnvariable$(ObjectSuffix) -MF$(IntermediateDirectory)/nnvariable$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariable.cpp"

$(IntermediateDirectory)/nnvariablecategory$(ObjectSuffix): aiengine/src/modnnlib/nnvariablecategory.cpp $(IntermediateDirectory)/nnvariablecategory$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariablecategory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnvariablecategory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnvariablecategory$(DependSuffix): aiengine/src/modnnlib/nnvariablecategory.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnvariablecategory$(ObjectSuffix) -MF$(IntermediateDirectory)/nnvariablecategory$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariablecategory.cpp"

$(IntermediateDirectory)/nnvariables$(ObjectSuffix): aiengine/src/modnnlib/nnvariables.cpp $(IntermediateDirectory)/nnvariables$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariables.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnvariables$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnvariables$(DependSuffix): aiengine/src/modnnlib/nnvariables.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnvariables$(ObjectSuffix) -MF$(IntermediateDirectory)/nnvariables$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariables.cpp"

$(IntermediateDirectory)/nnvariablescontainer$(ObjectSuffix): aiengine/src/modnnlib/nnvariablescontainer.cpp $(IntermediateDirectory)/nnvariablescontainer$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariablescontainer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnvariablescontainer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnvariablescontainer$(DependSuffix): aiengine/src/modnnlib/nnvariablescontainer.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnvariablescontainer$(ObjectSuffix) -MF$(IntermediateDirectory)/nnvariablescontainer$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariablescontainer.cpp"

$(IntermediateDirectory)/nnvariablesimple$(ObjectSuffix): aiengine/src/modnnlib/nnvariablesimple.cpp $(IntermediateDirectory)/nnvariablesimple$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariablesimple.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnvariablesimple$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnvariablesimple$(DependSuffix): aiengine/src/modnnlib/nnvariablesimple.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnvariablesimple$(ObjectSuffix) -MF$(IntermediateDirectory)/nnvariablesimple$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnvariablesimple.cpp"

$(IntermediateDirectory)/nnweights$(ObjectSuffix): aiengine/src/modnnlib/nnweights.cpp $(IntermediateDirectory)/nnweights$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnweights.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nnweights$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nnweights$(DependSuffix): aiengine/src/modnnlib/nnweights.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nnweights$(ObjectSuffix) -MF$(IntermediateDirectory)/nnweights$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modnnlib/nnweights.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/nn$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nn$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nn$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnactivationfunction$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnactivationfunction$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnactivationfunction$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnerrorfunction$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnerrorfunction$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnerrorfunction$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnfinder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnfinder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnfinder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnfinderfactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnfinderfactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnfinderfactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnfinderfactorysample$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnfinderfactorysample$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnfinderfactorysample$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nninductionfunction$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nninductionfunction$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nninductionfunction$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnlayer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnlayer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnlayer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnlib$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnlib$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnlib$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnlibdebug$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnlibdebug$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnlibdebug$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnneuron$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnneuron$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnneuron$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnregression$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnregression$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnregression$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnregressionfactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnregressionfactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnregressionfactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnsample$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnsample$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnsample$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnsamples$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnsamples$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnsamples$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnscanpoint$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnscanpoint$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnscanpoint$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnstopfunction$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnstopfunction$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnstopfunction$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategy$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategy$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategy$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategybackpropagation$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategybackpropagation$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategybackpropagation$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyhelper$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyhelper$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyhelper$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyscan$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyscan$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyscan$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyscaniteration$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyscaniteration$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnstrategyscaniteration$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnvalidatefunction$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnvalidatefunction$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnvalidatefunction$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnvariable$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnvariable$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnvariable$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablecategory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablecategory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablecategory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnvariables$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnvariables$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnvariables$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablescontainer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablescontainer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablescontainer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablesimple$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablesimple$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnvariablesimple$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nnweights$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nnweights$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nnweights$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


