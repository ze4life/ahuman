##
## Auto Generated makefile, please do not edit
##
ProjectName:=modio

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


Objects=$(IntermediateDirectory)/channel$(ObjectSuffix) $(IntermediateDirectory)/io$(ObjectSuffix) $(IntermediateDirectory)/message$(ObjectSuffix) $(IntermediateDirectory)/publisher$(ObjectSuffix) $(IntermediateDirectory)/queue$(ObjectSuffix) $(IntermediateDirectory)/session$(ObjectSuffix) $(IntermediateDirectory)/subscription$(ObjectSuffix) $(IntermediateDirectory)/xmlcall$(ObjectSuffix) $(IntermediateDirectory)/xmlmessage$(ObjectSuffix) 

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
$(IntermediateDirectory)/channel$(ObjectSuffix): aiengine/src/modio/channel.cpp $(IntermediateDirectory)/channel$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/channel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/channel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/channel$(DependSuffix): aiengine/src/modio/channel.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/channel$(ObjectSuffix) -MF$(IntermediateDirectory)/channel$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/channel.cpp"

$(IntermediateDirectory)/io$(ObjectSuffix): aiengine/src/modio/io.cpp $(IntermediateDirectory)/io$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/io.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/io$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/io$(DependSuffix): aiengine/src/modio/io.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/io$(ObjectSuffix) -MF$(IntermediateDirectory)/io$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/io.cpp"

$(IntermediateDirectory)/message$(ObjectSuffix): aiengine/src/modio/message.cpp $(IntermediateDirectory)/message$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/message.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/message$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/message$(DependSuffix): aiengine/src/modio/message.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/message$(ObjectSuffix) -MF$(IntermediateDirectory)/message$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/message.cpp"

$(IntermediateDirectory)/publisher$(ObjectSuffix): aiengine/src/modio/publisher.cpp $(IntermediateDirectory)/publisher$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/publisher.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/publisher$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/publisher$(DependSuffix): aiengine/src/modio/publisher.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/publisher$(ObjectSuffix) -MF$(IntermediateDirectory)/publisher$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/publisher.cpp"

$(IntermediateDirectory)/queue$(ObjectSuffix): aiengine/src/modio/queue.cpp $(IntermediateDirectory)/queue$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/queue.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/queue$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/queue$(DependSuffix): aiengine/src/modio/queue.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/queue$(ObjectSuffix) -MF$(IntermediateDirectory)/queue$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/queue.cpp"

$(IntermediateDirectory)/session$(ObjectSuffix): aiengine/src/modio/session.cpp $(IntermediateDirectory)/session$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/session.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/session$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/session$(DependSuffix): aiengine/src/modio/session.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/session$(ObjectSuffix) -MF$(IntermediateDirectory)/session$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/session.cpp"

$(IntermediateDirectory)/subscription$(ObjectSuffix): aiengine/src/modio/subscription.cpp $(IntermediateDirectory)/subscription$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/subscription.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/subscription$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/subscription$(DependSuffix): aiengine/src/modio/subscription.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/subscription$(ObjectSuffix) -MF$(IntermediateDirectory)/subscription$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/subscription.cpp"

$(IntermediateDirectory)/xmlcall$(ObjectSuffix): aiengine/src/modio/xmlcall.cpp $(IntermediateDirectory)/xmlcall$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/xmlcall.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/xmlcall$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/xmlcall$(DependSuffix): aiengine/src/modio/xmlcall.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/xmlcall$(ObjectSuffix) -MF$(IntermediateDirectory)/xmlcall$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/xmlcall.cpp"

$(IntermediateDirectory)/xmlmessage$(ObjectSuffix): aiengine/src/modio/xmlmessage.cpp $(IntermediateDirectory)/xmlmessage$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/xmlmessage.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/xmlmessage$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/xmlmessage$(DependSuffix): aiengine/src/modio/xmlmessage.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/xmlmessage$(ObjectSuffix) -MF$(IntermediateDirectory)/xmlmessage$(DependSuffix) -MM "E:/Personal/ahuman/Codelite Code migration/Ahuman/aiengine/src/modio/xmlmessage.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/channel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/channel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/channel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/io$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/io$(DependSuffix)
	$(RM) $(IntermediateDirectory)/io$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/message$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/message$(DependSuffix)
	$(RM) $(IntermediateDirectory)/message$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/publisher$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/publisher$(DependSuffix)
	$(RM) $(IntermediateDirectory)/publisher$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/queue$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/queue$(DependSuffix)
	$(RM) $(IntermediateDirectory)/queue$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/session$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/session$(DependSuffix)
	$(RM) $(IntermediateDirectory)/session$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/subscription$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/subscription$(DependSuffix)
	$(RM) $(IntermediateDirectory)/subscription$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/xmlcall$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/xmlcall$(DependSuffix)
	$(RM) $(IntermediateDirectory)/xmlcall$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/xmlmessage$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/xmlmessage$(DependSuffix)
	$(RM) $(IntermediateDirectory)/xmlmessage$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


