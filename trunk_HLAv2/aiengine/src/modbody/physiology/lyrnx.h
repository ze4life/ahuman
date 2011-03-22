#include "Windows.h"
#include "Mmsystem.h"
#include <stdlib.h>
#include <string.h>
#include "speak_lib.h"

int SynthCallback(short *wav, int numsamples, espeak_EVENT *events);
static FILE* f_wavfile ;

class lyrnx {
public:
	static void DisplayVoices(FILE *f_out, char *language){
		int ix;
		const char *p;
		int len;
		int count;
		int scores = 0;
		const espeak_VOICE *v;
		const char *lang_name;
		char age_buf[12];
		const espeak_VOICE **voices;
		espeak_VOICE voice_select;
		static char genders[4] = {' ','M','F',' '};
		if((language != NULL) && (language[0] != 0)){
			// display only voices for the specified language, in order of priority
			voice_select.languages = language;
			voice_select.age = 0;
			voice_select.gender = 0;
			voice_select.name = NULL;
			voices = espeak_ListVoices(&voice_select);
			scores = 1;
		}
		else{
			voices = espeak_ListVoices(NULL);
		}

		fprintf(f_out,"Pty Language Age/Gender VoiceName       File        Other Langs\n");

		for(ix=0; (v = voices[ix]) != NULL; ix++){
			count = 0;
			p = v->languages;
			while(*p != 0)	{
				len = strlen(p+1);
				lang_name = p+1;

				if(v->age == 0)
					strcpy(age_buf,"   ");
				else
					sprintf(age_buf,"%3d",v->age);

				if(count==0)
				{
					fprintf(f_out,"%2d  %-12s%s%c  %-17s %-11s ",
				   p[0],lang_name,age_buf,genders[v->gender],v->name,v->identifier);
				}
				else
				{
					fprintf(f_out,"(%s %d)",lang_name,p[0]);
				}
				count++;
				p += len+2;
			}
			fputc('\n',f_out);
		}
	}

	static void Write4Bytes(FILE *f, int value){
		int ix;
		for(ix=0; ix<4; ix++){
			fputc(value & 0xff,f);
			value = value >> 8;
		}
	}
	static int OpenWavFile(char *path, int rate){
		static unsigned char wave_hdr[44] = {
			'R','I','F','F',0x24,0xf0,0xff,0x7f,'W','A','V','E','f','m','t',' ',
			0x10,0,0,0,1,0,1,0,  9,0x3d,0,0,0x12,0x7a,0,0,
			2,0,0x10,0,'d','a','t','a',  0x00,0xf0,0xff,0x7f};

		f_wavfile = fopen(path,"wb");
		if(f_wavfile == NULL)
		{
			fprintf(stderr,"Can't write to: '%s'\n",path);
			return(1);
		}
		fwrite(wave_hdr,1,24,f_wavfile);
		Write4Bytes(f_wavfile,rate);
		Write4Bytes(f_wavfile,rate * 2);
		fwrite(&wave_hdr[32],1,12,f_wavfile);
		return(0);
	}
	static void CloseWavFile(){
		unsigned int pos;
		if(f_wavfile==NULL)
			return;
		fflush(f_wavfile);
		pos = ftell(f_wavfile);
		fseek(f_wavfile,4,SEEK_SET);
		Write4Bytes(f_wavfile,pos - 8);
		fseek(f_wavfile,40,SEEK_SET);
		Write4Bytes(f_wavfile,pos - 44);
		fclose(f_wavfile);
		f_wavfile = NULL;
	} 
	

	static int play (char* text){
		int synth_flags = espeakCHARS_AUTO | espeakPHONEMES | espeakENDPAUSE;
		int volume = 100;//-1;
		int speed = 150;//-1;
		int pitch = 30;//-1;
	
		espeak_VOICE voice_select;
		char voicename[40];
		voicename[0] = 0;
		int samplerateloc = espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS,4096,0,0);
		//DisplayVoices(stdout, NULL);	
		strcpy(voicename,"+f1");
		if(espeak_SetVoiceByName(voicename) != EE_OK)
		{
			memset(&voice_select,0,sizeof(voice_select));
			voice_select.languages = voicename;
			if(espeak_SetVoiceByProperties(&voice_select) != EE_OK){
				//fprintf(stderr,"%svoice '%s'\n",err_load,voicename);
				exit(2);
			}
		}
		// set any non-default values of parameters. This must be done after espeak_Initialize()
		if(speed > 0)
			espeak_SetParameter(espeakRATE,speed,0);
		if(volume >= 0)
			espeak_SetParameter(espeakVOLUME,volume,0);
		if(pitch >= 0)
			espeak_SetParameter(espeakPITCH,pitch,0);
	
		espeak_SetSynthCallback(SynthCallback);
		espeak_Synth( text,strlen(text)+1, 0, POS_CHARACTER, 0, synth_flags, NULL, NULL);
		espeak_Synchronize();
		PlaySound(TEXT("outaudio.wav"), NULL, SND_FILENAME | SND_SYNC);
		DeleteFile(TEXT("outaudio.wav"));
		return(0);
	}
};

static int SynthCallback(short *wav, int numsamples, espeak_EVENT *events){
		char fname[210];
		if(wav == NULL){
			lyrnx::CloseWavFile();
			return(0);
		}
		int samplerateloc = 0;
		while(events->type != 0){
			if(events->type == espeakEVENT_SAMPLERATE){
				samplerateloc = events->id.number;
			}
			events++;
		}

		if(f_wavfile == NULL){
			if(lyrnx::OpenWavFile("outaudio.wav", samplerateloc) != 0)
					return(1);
		
		}

		if(numsamples > 0){
			fwrite(wav,numsamples*2,1, f_wavfile);
		}
		return(0);
}
