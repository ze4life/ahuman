##
## Auto Generated makefile, please do not edit
##
ProjectName:=modhtm

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./aiengine/Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "E:\trunk\Ahuman"
ProjectPath            := "E:\trunk\Ahuman"
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


Objects=$(IntermediateDirectory)/htmcortex$(ObjectSuffix) $(IntermediateDirectory)/htmhelper$(ObjectSuffix) $(IntermediateDirectory)/htmlayer$(ObjectSuffix) $(IntermediateDirectory)/htmlayermemory$(ObjectSuffix) $(IntermediateDirectory)/htmlib$(ObjectSuffix) $(IntermediateDirectory)/htmlibdebug$(ObjectSuffix) $(IntermediateDirectory)/htmrect$(ObjectSuffix) $(IntermediateDirectory)/htmsequence$(ObjectSuffix) 

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
$(IntermediateDirectory)/htmcortex$(ObjectSuffix): aiengine/src/modhtmlib/htmcortex.cpp $(IntermediateDirectory)/htmcortex$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmcortex.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/htmcortex$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/htmcortex$(DependSuffix): aiengine/src/modhtmlib/htmcortex.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/htmcortex$(ObjectSuffix) -MF$(IntermediateDirectory)/htmcortex$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmcortex.cpp"

$(IntermediateDirectory)/htmhelper$(ObjectSuffix): aiengine/src/modhtmlib/htmhelper.cpp $(IntermediateDirectory)/htmhelper$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmhelper.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/htmhelper$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/htmhelper$(DependSuffix): aiengine/src/modhtmlib/htmhelper.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/htmhelper$(ObjectSuffix) -MF$(IntermediateDirectory)/htmhelper$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmhelper.cpp"

$(IntermediateDirectory)/htmlayer$(ObjectSuffix): aiengine/src/modhtmlib/htmlayer.cpp $(IntermediateDirectory)/htmlayer$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmlayer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/htmlayer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/htmlayer$(DependSuffix): aiengine/src/modhtmlib/htmlayer.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/htmlayer$(ObjectSuffix) -MF$(IntermediateDirectory)/htmlayer$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmlayer.cpp"

$(IntermediateDirectory)/htmlayermemory$(ObjectSuffix): aiengine/src/modhtmlib/htmlayermemory.cpp $(IntermediateDirectory)/htmlayermemory$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmlayermemory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/htmlayermemory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/htmlayermemory$(DependSuffix): aiengine/src/modhtmlib/htmlayermemory.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/htmlayermemory$(ObjectSuffix) -MF$(IntermediateDirectory)/htmlayermemory$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmlayermemory.cpp"

$(IntermediateDirectory)/htmlib$(ObjectSuffix): aiengine/src/modhtmlib/htmlib.cpp $(IntermediateDirectory)/htmlib$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmlib.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/htmlib$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/htmlib$(DependSuffix): aiengine/src/modhtmlib/htmlib.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/htmlib$(ObjectSuffix) -MF$(IntermediateDirectory)/htmlib$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmlib.cpp"

$(IntermediateDirectory)/htmlibdebug$(ObjectSuffix): aiengine/src/modhtmlib/htmlibdebug.cpp $(IntermediateDirectory)/htmlibdebug$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmlibdebug.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/htmlibdebug$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/htmlibdebug$(DependSuffix): aiengine/src/modhtmlib/htmlibdebug.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/htmlibdebug$(ObjectSuffix) -MF$(IntermediateDirectory)/htmlibdebug$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmlibdebug.cpp"

$(IntermediateDirectory)/htmrect$(ObjectSuffix): aiengine/src/modhtmlib/htmrect.cpp $(IntermediateDirectory)/htmrect$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmrect.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/htmrect$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/htmrect$(DependSuffix): aiengine/src/modhtmlib/htmrect.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/htmrect$(ObjectSuffix) -MF$(IntermediateDirectory)/htmrect$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmrect.cpp"

$(IntermediateDirectory)/htmsequence$(ObjectSuffix): aiengine/src/modhtmlib/htmsequence.cpp $(IntermediateDirectory)/htmsequence$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmsequence.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/htmsequence$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/htmsequence$(DependSuffix): aiengine/src/modhtmlib/htmsequence.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/htmsequence$(ObjectSuffix) -MF$(IntermediateDirectory)/htmsequence$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/modhtmlib/htmsequence.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/htmcortex$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/htmcortex$(DependSuffix)
	$(RM) $(IntermediateDirectory)/htmcortex$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/htmhelper$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/htmhelper$(DependSuffix)
	$(RM) $(IntermediateDirectory)/htmhelper$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/htmlayer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/htmlayer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/htmlayer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/htmlayermemory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/htmlayermemory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/htmlayermemory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/htmlib$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/htmlib$(DependSuffix)
	$(RM) $(IntermediateDirectory)/htmlib$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/htmlibdebug$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/htmlibdebug$(DependSuffix)
	$(RM) $(IntermediateDirectory)/htmlibdebug$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/htmrect$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/htmrect$(DependSuffix)
	$(RM) $(IntermediateDirectory)/htmrect$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/htmsequence$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/htmsequence$(DependSuffix)
	$(RM) $(IntermediateDirectory)/htmsequence$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


