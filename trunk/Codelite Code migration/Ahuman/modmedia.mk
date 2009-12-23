##
## Auto Generated makefile, please do not edit
##
ProjectName:=modmedia

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
IncludePath            := "$(IncludeSwitch)." "$(IncludeSwitch)./aiengine/include" "$(IncludeSwitch)./aiengine/src/include" "$(IncludeSwitch)./generic/include" "$(IncludeSwitch)./generic/include/stacktrace"  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)./aiengine/include" "$(IncludeSwitch)./aiengine/src/include" "$(IncludeSwitch)./generic/include" "$(IncludeSwitch)./generic/include/stacktrace" "$(IncludeSwitch)./aiapi/include" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)aiapi $(LibrarySwitch)wsock32 $(LibrarySwitch)ws2_32 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)./lib" 


Objects=$(IntermediateDirectory)/listener$(ObjectSuffix) $(IntermediateDirectory)/media$(ObjectSuffix) $(IntermediateDirectory)/socketconnection$(ObjectSuffix) $(IntermediateDirectory)/sockserver$(ObjectSuffix) 

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
$(IntermediateDirectory)/listener$(ObjectSuffix): aiengine/src/modmedia/listener.cpp $(IntermediateDirectory)/listener$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modmedia/listener.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/listener$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/listener$(DependSuffix): aiengine/src/modmedia/listener.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/listener$(ObjectSuffix) -MF$(IntermediateDirectory)/listener$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modmedia/listener.cpp"

$(IntermediateDirectory)/media$(ObjectSuffix): aiengine/src/modmedia/media.cpp $(IntermediateDirectory)/media$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modmedia/media.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/media$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/media$(DependSuffix): aiengine/src/modmedia/media.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/media$(ObjectSuffix) -MF$(IntermediateDirectory)/media$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modmedia/media.cpp"

$(IntermediateDirectory)/socketconnection$(ObjectSuffix): aiengine/src/modmedia/socketconnection.cpp $(IntermediateDirectory)/socketconnection$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modmedia/socketconnection.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/socketconnection$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/socketconnection$(DependSuffix): aiengine/src/modmedia/socketconnection.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/socketconnection$(ObjectSuffix) -MF$(IntermediateDirectory)/socketconnection$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modmedia/socketconnection.cpp"

$(IntermediateDirectory)/sockserver$(ObjectSuffix): aiengine/src/modmedia/sockserver.cpp $(IntermediateDirectory)/sockserver$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modmedia/sockserver.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sockserver$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sockserver$(DependSuffix): aiengine/src/modmedia/sockserver.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sockserver$(ObjectSuffix) -MF$(IntermediateDirectory)/sockserver$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modmedia/sockserver.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/listener$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/listener$(DependSuffix)
	$(RM) $(IntermediateDirectory)/listener$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/media$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/media$(DependSuffix)
	$(RM) $(IntermediateDirectory)/media$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/socketconnection$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/socketconnection$(DependSuffix)
	$(RM) $(IntermediateDirectory)/socketconnection$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sockserver$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sockserver$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sockserver$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


