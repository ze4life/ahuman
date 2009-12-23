##
## Auto Generated makefile, please do not edit
##
ProjectName:=fann

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./fann/Debug
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)./fann/include" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/doublefann$(ObjectSuffix) $(IntermediateDirectory)/fann$(ObjectSuffix) $(IntermediateDirectory)/fann_cascade$(ObjectSuffix) $(IntermediateDirectory)/fann_error$(ObjectSuffix) $(IntermediateDirectory)/fann_io$(ObjectSuffix) $(IntermediateDirectory)/fann_train$(ObjectSuffix) $(IntermediateDirectory)/fann_train_data$(ObjectSuffix) $(IntermediateDirectory)/fixedfann$(ObjectSuffix) $(IntermediateDirectory)/floatfann$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@makedir $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

./fann/Debug:
	@makedir "./fann/Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/doublefann$(ObjectSuffix): fann/src/doublefann.c $(IntermediateDirectory)/doublefann$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/doublefann.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/doublefann$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/doublefann$(DependSuffix): fann/src/doublefann.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/doublefann$(ObjectSuffix) -MF$(IntermediateDirectory)/doublefann$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/doublefann.c"

$(IntermediateDirectory)/fann$(ObjectSuffix): fann/src/fann.c $(IntermediateDirectory)/fann$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/fann.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/fann$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fann$(DependSuffix): fann/src/fann.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/fann$(ObjectSuffix) -MF$(IntermediateDirectory)/fann$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/fann.c"

$(IntermediateDirectory)/fann_cascade$(ObjectSuffix): fann/src/fann_cascade.c $(IntermediateDirectory)/fann_cascade$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/fann_cascade.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/fann_cascade$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fann_cascade$(DependSuffix): fann/src/fann_cascade.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/fann_cascade$(ObjectSuffix) -MF$(IntermediateDirectory)/fann_cascade$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/fann_cascade.c"

$(IntermediateDirectory)/fann_error$(ObjectSuffix): fann/src/fann_error.c $(IntermediateDirectory)/fann_error$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/fann_error.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/fann_error$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fann_error$(DependSuffix): fann/src/fann_error.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/fann_error$(ObjectSuffix) -MF$(IntermediateDirectory)/fann_error$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/fann_error.c"

$(IntermediateDirectory)/fann_io$(ObjectSuffix): fann/src/fann_io.c $(IntermediateDirectory)/fann_io$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/fann_io.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/fann_io$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fann_io$(DependSuffix): fann/src/fann_io.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/fann_io$(ObjectSuffix) -MF$(IntermediateDirectory)/fann_io$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/fann_io.c"

$(IntermediateDirectory)/fann_train$(ObjectSuffix): fann/src/fann_train.c $(IntermediateDirectory)/fann_train$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/fann_train.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/fann_train$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fann_train$(DependSuffix): fann/src/fann_train.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/fann_train$(ObjectSuffix) -MF$(IntermediateDirectory)/fann_train$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/fann_train.c"

$(IntermediateDirectory)/fann_train_data$(ObjectSuffix): fann/src/fann_train_data.c $(IntermediateDirectory)/fann_train_data$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/fann_train_data.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/fann_train_data$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fann_train_data$(DependSuffix): fann/src/fann_train_data.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/fann_train_data$(ObjectSuffix) -MF$(IntermediateDirectory)/fann_train_data$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/fann_train_data.c"

$(IntermediateDirectory)/fixedfann$(ObjectSuffix): fann/src/fixedfann.c $(IntermediateDirectory)/fixedfann$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/fixedfann.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/fixedfann$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fixedfann$(DependSuffix): fann/src/fixedfann.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/fixedfann$(ObjectSuffix) -MF$(IntermediateDirectory)/fixedfann$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/fixedfann.c"

$(IntermediateDirectory)/floatfann$(ObjectSuffix): fann/src/floatfann.c $(IntermediateDirectory)/floatfann$(DependSuffix)
	@makedir "./fann/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/fann/src/floatfann.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/floatfann$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/floatfann$(DependSuffix): fann/src/floatfann.c
	@makedir "./fann/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/floatfann$(ObjectSuffix) -MF$(IntermediateDirectory)/floatfann$(DependSuffix) -MM "E:/trunk/Ahuman/fann/src/floatfann.c"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/doublefann$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/doublefann$(DependSuffix)
	$(RM) $(IntermediateDirectory)/doublefann$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/fann$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/fann$(DependSuffix)
	$(RM) $(IntermediateDirectory)/fann$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/fann_cascade$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/fann_cascade$(DependSuffix)
	$(RM) $(IntermediateDirectory)/fann_cascade$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/fann_error$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/fann_error$(DependSuffix)
	$(RM) $(IntermediateDirectory)/fann_error$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/fann_io$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/fann_io$(DependSuffix)
	$(RM) $(IntermediateDirectory)/fann_io$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/fann_train$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/fann_train$(DependSuffix)
	$(RM) $(IntermediateDirectory)/fann_train$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/fann_train_data$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/fann_train_data$(DependSuffix)
	$(RM) $(IntermediateDirectory)/fann_train_data$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/fixedfann$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/fixedfann$(DependSuffix)
	$(RM) $(IntermediateDirectory)/fixedfann$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/floatfann$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/floatfann$(DependSuffix)
	$(RM) $(IntermediateDirectory)/floatfann$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


