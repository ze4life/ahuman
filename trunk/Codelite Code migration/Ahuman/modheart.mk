##
## Auto Generated makefile, please do not edit
##
ProjectName:=modheart

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


Objects=$(IntermediateDirectory)/emotion$(ObjectSuffix) $(IntermediateDirectory)/heart$(ObjectSuffix) 

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
$(IntermediateDirectory)/emotion$(ObjectSuffix): aiengine/src/modheart/emotion.cpp $(IntermediateDirectory)/emotion$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modheart/emotion.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/emotion$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/emotion$(DependSuffix): aiengine/src/modheart/emotion.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/emotion$(ObjectSuffix) -MF$(IntermediateDirectory)/emotion$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modheart/emotion.cpp"

$(IntermediateDirectory)/heart$(ObjectSuffix): aiengine/src/modheart/heart.cpp $(IntermediateDirectory)/heart$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modheart/heart.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/heart$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/heart$(DependSuffix): aiengine/src/modheart/heart.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/heart$(ObjectSuffix) -MF$(IntermediateDirectory)/heart$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modheart/heart.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/emotion$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/emotion$(DependSuffix)
	$(RM) $(IntermediateDirectory)/emotion$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/heart$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/heart$(DependSuffix)
	$(RM) $(IntermediateDirectory)/heart$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


