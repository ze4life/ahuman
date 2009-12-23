##
## Auto Generated makefile, please do not edit
##
ProjectName:=modknowledge

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
IncludePath            := "$(IncludeSwitch)." "$(IncludeSwitch)./aiengine/include" "$(IncludeSwitch)./aiengine/src/include" "$(IncludeSwitch)./generic/include" "$(IncludeSwitch)./generic/include/stacktrace"  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)./generic/include" "$(IncludeSwitch)./generic/include/stacktrace" "$(IncludeSwitch)./aiengine/include" "$(IncludeSwitch)./aiengine/src/include" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/knowledge$(ObjectSuffix) 

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
$(IntermediateDirectory)/knowledge$(ObjectSuffix): aiengine/src/modknowledge/knowledge.cpp $(IntermediateDirectory)/knowledge$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modknowledge/knowledge.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/knowledge$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/knowledge$(DependSuffix): aiengine/src/modknowledge/knowledge.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/knowledge$(ObjectSuffix) -MF$(IntermediateDirectory)/knowledge$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modknowledge/knowledge.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/knowledge$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/knowledge$(DependSuffix)
	$(RM) $(IntermediateDirectory)/knowledge$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


