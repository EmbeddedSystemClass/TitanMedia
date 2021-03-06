#include "srk_defs.h"
#pragma hdrstop
#include "srk_data_types.h"
#include "srk_codec_io.h"
#include "srk_crypt.h"

/*
	Sonork Messaging System

	Portions Copyright (C) 2001 Sonork SRL:

	This program is free software; you can redistribute it and/or modify
	it under the terms of the Sonork Source Code License (SSCL) Version 1.

	You should have received a copy of the SSCL	along with this program;
	if not, write to sscl@sonork.com.

	You should NOT use this source code before reading and accepting the
	Sonork Source Code License (SSCL), doing so will indicate your agreement
	to the the terms which may be differ for each version of the software.

	This comment section, indicating the existence and requirement of
	acceptance of the SSCL may not be removed from the source code.
*/

#if SONORK_CODEC_LEVEL>5
//bool sonork_codec_io_v104_compatibility_mode=false;


// ----------------------------------------------------------------------------
// TSonorkP2Mapping
// ----------------------------------------------------------------------------
void
 TSonorkP2Mapping::Set( const TSonorkP2Mapping& O )
{
	memcpy(&header,&O.header,sizeof(header));
	mapperHost.Set(O.mapperHost);
	socksHost.Set(O.socksHost);
}
void
 TSonorkP2Mapping::Clear()
{
	memset(&header,0,sizeof(header));
	mapperHost.Clear();
	socksHost.Clear();
}


DWORD
 TSonorkP2Mapping::CODEC_DataSize(DWORD ) const
{
	DWORD aux=sizeof(DWORD)+sizeof(header);
	aux+=::CODEC_Size(&mapperHost);
	aux+=::CODEC_Size(&socksHost);
	return aux;
}

void
 TSonorkP2Mapping::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN((DWORD*)&header,SIZEOF_IN_DWORDS(header));
	CODEC.Write(&mapperHost);
	CODEC.Write(&socksHost);
}

void
 TSonorkP2Mapping::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	aux;
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN((DWORD*)&header,SIZEOF_IN_DWORDS(header));
	CODEC.Skip((aux&0xfff)-sizeof(header));
	CODEC.Read(&mapperHost);
	CODEC.Read(&socksHost);
}

// ----------------------------------------------------------------------------
// TSonorkLocus
// ----------------------------------------------------------------------------
void
 TSonorkLocusAtom::Set(const TSonorkLocusAtom& O)
{
	memcpy(&userLocusEx,&O.userLocusEx,sizeof(userLocusEx));
}

void
 TSonorkLocusAtom::Clear()
{
	memset(&userLocusEx,0,sizeof(userLocusEx));
}

void
 TSonorkLocusAtom::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(TSonorkUserLocus));
	CODEC.WriteDWN( (DWORD*)&userLocusEx , SIZEOF_IN_DWORDS(TSonorkUserLocus) );
	CODEC.WritePA1(&userLocusEx.utsAddr);
	CODEC.WritePA1(&userLocusEx.hostAddr);
}

void
 TSonorkLocusAtom::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	aux;
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN( (DWORD*)&userLocusEx , SIZEOF_IN_DWORDS(TSonorkUserLocus) );
	CODEC.Skip((aux&0xfff)-sizeof(TSonorkUserLocus));
	CODEC.ReadPA1(&userLocusEx.utsAddr);
	CODEC.ReadPA1(&userLocusEx.hostAddr);
}

DWORD
 TSonorkLocusAtom::CODEC_DataSize(DWORD ) const
{
	return sizeof(DWORD)
		+sizeof(TSonorkUserLocus)
		+::CODEC_Size(&userLocusEx.utsAddr)
		+::CODEC_Size(&userLocusEx.hostAddr);
}

// ----------------------------------------------------------------------------
// TSonorkUserAddr
// ----------------------------------------------------------------------------
void
 TSonorkP2Descriptor::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
}

void
 TSonorkP2Descriptor::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
//	DWORD	aux;
	CODEC.Skip(sizeof(DWORD));
	CODEC.ReadDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	// CODEC.Skip((aux&0xfff)-sizeof(header));
}

DWORD
 TSonorkP2Descriptor::CODEC_DataSize(DWORD ) const
{
	return sizeof(DWORD)+sizeof(HEADER);
}

// ----------------------------------------------------------------------------
// TSonorkUserAddr
// ----------------------------------------------------------------------------

void
 TSonorkUserAddr::Set(const TSonorkUserAddr& O)
{
	memcpy(&header,&O.header,sizeof(header)+sizeof(TSonorkPhysAddr)*2);
}

void
 TSonorkUserAddr::Clear()
{
	memset(&header,0,sizeof(header)+sizeof(TSonorkPhysAddr)*2);
}

void
  TSonorkUserAddr::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.WritePA1(&utsAddr);
	CODEC.WritePA1(&hostAddr);
}

void
 TSonorkUserAddr::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	aux;
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Skip((aux&0xfff)-sizeof(header));
	CODEC.ReadPA1(&utsAddr);
	CODEC.ReadPA1(&hostAddr);
}

DWORD
 TSonorkUserAddr::CODEC_DataSize(DWORD ) const
{
	return sizeof(DWORD)
		+sizeof(header)
		+::CODEC_Size(&utsAddr)
		+::CODEC_Size(&hostAddr);
}

// ----------------------------------------------------------------------------
// TSonorkServiceLocus
// ----------------------------------------------------------------------------

void
 TSonorkServiceLocus::Clear()
{
	memset(&info,0,sizeof(info));
	locus.Clear();
}

void
 TSonorkServiceLocus::Set(const TSonorkServiceLocus& O)
{
	memcpy(&info,&O.info,sizeof(info));
	locus.Set(O.locus);
}

void
 TSonorkServiceLocus::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(info));
	CODEC.WriteDWN( (DWORD*)&info , SIZEOF_IN_DWORDS(info) );
	CODEC.Write(&locus);
}

void
 TSonorkServiceLocus::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	aux;
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN( (DWORD*)&info , SIZEOF_IN_DWORDS(info) );
	CODEC.Skip((aux&0xfff)-sizeof(info));
	CODEC.Read(&locus);
}

DWORD
 TSonorkServiceLocus::CODEC_DataSize(DWORD codecVersion) const
{
	return sizeof(DWORD)+sizeof(info)+locus.CODEC_Size(codecVersion);
}

// ----------------------------------------------------------------------------
// TSonorkSidNotificationAtom
// ----------------------------------------------------------------------------


void
 TSonorkSidNotification::Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
	locus.Clear();
	text.Clear();
}
void
 TSonorkSidNotification::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	if( CODEC.Version() < SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		CODEC.WriteDW( sizeof(OLD_HEADER) );
		CODEC.WriteDW4( &locus.userLocusEx.version );
		CODEC.WriteDW2( &header.userSerial );
		CODEC.Skip(sizeof(DWORD)*4);
		CODEC.WriteUL3_obsolete( &locus  );
	}
	else
	{
		CODEC.WriteDW( sizeof(HEADER) );
		CODEC.WriteDWN( (const DWORD*)&header , SIZEOF_IN_DWORDS(header) );
		CODEC.Write(&locus);

	}
	CODEC.Write(&text);
}
void
 TSonorkSidNotification::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	aux;

	if( CODEC.DataType() != CODEC_DataType())
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW(&aux);
	if( CODEC.Version() < SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		CODEC.ReadDW4( &locus.userLocusEx.version );
		CODEC.ReadDW2( &header.userSerial );
		CODEC.Skip( (aux&0xfff) - (sizeof(DWORD)*6) );

		CODEC.ReadUL3_obsolete( &locus  );
	}
	else
	{
		CODEC.ReadDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
		CODEC.Skip( (aux&0xfff) - sizeof(HEADER) );
		CODEC.Read(&locus);
	}
	CODEC.Read(&text);

}

DWORD
 TSonorkSidNotification::CODEC_DataSize(DWORD codecVersion) const
{
	if( codecVersion < SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		return sizeof(DWORD)
			+sizeof(OLD_HEADER)
			+CODEC_Locus3Size_obsolete( &locus )
			+text.CODEC_Size(codecVersion);
	}
	else
	{

		return sizeof(DWORD)
			+sizeof(HEADER)
			+locus.CODEC_Size(codecVersion)
			+text.CODEC_Size(codecVersion);
	}

}


// ----------------------------------------------------------------------------
// TSonorkUserServer
// ----------------------------------------------------------------------------
#define SONORK_USER_SERVER_CODEC_F_NULL_ADDR	0x00010000
void
 TSonorkUserServer::Clear()
{
	SONORK_ZeroMem(&serverAddr,sizeof(serverAddr));
	name.Clear();
	text.Clear();
	data.Clear();
}
DWORD
 TSonorkUserServer::CODEC_DataSize(DWORD codecVersion)	const
{
	DWORD aux;
	if( codecVersion >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		aux=sizeof(DWORD) +sizeof(TSonorkNewUserServerHeader);
		aux+= ::CODEC_Size( &serverAddr.hostAddr );
	}
	else
	{
		aux=sizeof(DWORD) +sizeof(TSonorkOldUserServerHeader);
	}
	aux+=::CODEC_Size( &serverAddr.utsAddr );
	aux+=name.CODEC_Size(codecVersion);
	aux+=text.CODEC_Size(codecVersion);
	aux+=data.CODEC_Size(codecVersion);
	return aux;

}
void
 TSonorkUserServer::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	if( CODEC.Version() >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		CODEC.WriteDW(  sizeof(TSonorkNewUserServerHeader)  );
		CODEC.WriteDWN( (DWORD*)&serverAddr , SIZEOF_IN_DWORDS(TSonorkNewUserServerHeader) );
		CODEC.WritePA1( &serverAddr.utsAddr);
		CODEC.WritePA1( &serverAddr.hostAddr);
	}
	else
	{
		CODEC.WriteDW( sizeof(TSonorkOldUserServerHeader)  );
		CODEC.WriteDWN( (DWORD*)&serverAddr , SIZEOF_IN_DWORDS(TSonorkOldUserServerHeader) );
		CODEC.WritePA1(&serverAddr.utsAddr);
	}
	CODEC.Write(&name);
	CODEC.Write(&text);
	CODEC.Write(&data);
}
void
 TSonorkUserServer::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD 	aux,headerSize;

	CODEC.ReadDW( &aux );
	headerSize=(aux&0xfff);

	if( CODEC.Version() >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		CODEC.ReadDWN((DWORD*)&serverAddr,SIZEOF_IN_DWORDS(TSonorkNewUserServerHeader));
		CODEC.Skip( headerSize - sizeof(TSonorkNewUserServerHeader));
		CODEC.ReadPA1(&serverAddr.utsAddr );
		CODEC.ReadPA1(&serverAddr.hostAddr );

	}
	else
	{
		CODEC.ReadDWN((DWORD*)&serverAddr,SIZEOF_IN_DWORDS(TSonorkOldUserServerHeader));
		CODEC.Skip( headerSize - sizeof(TSonorkOldUserServerHeader));
		if( !(aux&SONORK_USER_SERVER_CODEC_F_NULL_ADDR) )
			CODEC.ReadPA1(&serverAddr.utsAddr );
		serverAddr.hostAddr.Set(serverAddr.utsAddr);
	}

	CODEC.Read(&name);
	CODEC.Read(&text);
	CODEC.Read(&data);
}



// ----------------------------------------------------------------------------
// TSonorkAppCtrlData
// ----------------------------------------------------------------------------

void
 TSonorkAppCtrlData::CODEC_Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
}

void
 TSonorkAppCtrlData::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(0);
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN((DWORD*)&header,SIZEOF_IN_DWORDS(header));
}

void
 TSonorkAppCtrlData::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD 	aux;
	if( CODEC.DataType() != CODEC_DataType())
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW(&aux);
	if((aux&0xff)!=0)return;
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN((DWORD*)&header,SIZEOF_IN_DWORDS(header));
	CODEC.Skip((aux&0xfff) - sizeof(header));
}

DWORD
 TSonorkAppCtrlData::CODEC_DataSize(DWORD)	const
{
	return sizeof(DWORD)*2
		+sizeof(header);
}

// ----------------------------------------------------------------------------
// TSonorkProfileCtrlData
// ----------------------------------------------------------------------------

void
 TSonorkProfileCtrlData::CODEC_Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
	header.sidFlags.SetSidMode(SONORK_SID_MODE_ONLINE);
	serverProfile.Clear();
}
void
 TSonorkProfileCtrlData::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(
		 TSonorkProfileCtrlData::CODEC_F_HAS_SERVER_PROFILE
		|TSonorkProfileCtrlData::CODEC_V_VERSION_V10500
		);
	CODEC.WriteDW( sizeof(header) );
	CODEC.WriteDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&serverProfile);
}

void
 TSonorkProfileCtrlData::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD 	codec_flags,codec_header_size;
	if( CODEC.DataType() != CODEC_DataType())
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW( &codec_flags );
	CODEC.ReadDW( &codec_header_size);
	codec_header_size&=0xfff;
	if(  codec_header_size < sizeof(header) )
	{
		CODEC.ReadDWN( (DWORD*)&header , SIZE_IN_DWORDS(codec_header_size) );
		SONORK_ZeroMem(
			  ((BYTE*)&header) + codec_header_size
			 , sizeof(header) - codec_header_size);
	}
	else
	{
		CODEC.ReadDWN( (DWORD*)&header	, SIZEOF_IN_DWORDS(header) );
		CODEC.Skip(codec_header_size - sizeof(header));

	}

	if(codec_flags&(TSonorkProfileCtrlData::CODEC_F_HAS_SERVER_PROFILE))
		CODEC.Read(&serverProfile);
	else
		serverProfile.Clear();

}

DWORD
 TSonorkProfileCtrlData::CODEC_DataSize(DWORD)	const
{
	return sizeof(DWORD)*2
		+ sizeof(header)
		+::CODEC_Size(&serverProfile);

}


// ----------------------------------------------------------------------------
// TSonorkAuthReqData
// ----------------------------------------------------------------------------
void
 TSonorkAuthReqData::CODEC_Clear()
{
	SONORK_ZeroMem( &header , sizeof(header) );
	userData.Clear();
	notes.Clear();
}
void
 TSonorkAuthReqData::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(0);
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&userData);
	CODEC.Write(&notes);
}

void
 TSonorkAuthReqData::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD aux;

	if( CODEC.DataType() != CODEC_DataType())
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW(&aux);
	if((aux&0xff)!=0)
	{
		CODEC_Clear();
		return;
	}
	CODEC.ReadDW(&aux);
	aux&=0xfff;
	CODEC.ReadDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Skip(aux - sizeof(header));
	CODEC.Read(&userData);
	CODEC.Read(&notes);
}

DWORD
 TSonorkAuthReqData::CODEC_DataSize(DWORD version) const
{
	return sizeof(DWORD)*2
		+ sizeof(header)
		+ userData.CODEC_Size(version)
		+ notes.CODEC_Size(version);
}

// ----------------------------------------------------------------------------
// TSonorkServerAddr
// ----------------------------------------------------------------------------
void
 TSonorkServerAddr::CODEC_WriteDataMem	(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(0);
	CODEC.WriteDW(sizeof(ctrlData));
	CODEC.WriteDWN((DWORD*)&ctrlData , SIZEOF_IN_DWORDS(ctrlData) );
	CODEC.Write(&host);
}

void
 TSonorkServerAddr::CODEC_ReadDataMem	(TSonorkCodecReader& CODEC)
{
	DWORD	aux;
	if( CODEC.DataType() != CODEC_DataType() )
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}

	CODEC.ReadDW(&aux);
	if( (aux&0xff)==0 )
	{
		CODEC.ReadDW(&aux);
		CODEC.ReadDWN((DWORD*)&ctrlData , SIZEOF_IN_DWORDS(ctrlData) );
		CODEC.Skip(aux - sizeof(ctrlData));
		CODEC.Read(&host);
	}
}

DWORD
 TSonorkServerAddr::CODEC_DataSize(DWORD )	const
{
	return sizeof(DWORD)*2
		+  sizeof(ctrlData)
		+  ::CODEC_Size(&host);
}

void
 TSonorkServerAddr::Clear()
{
	host.Clear();
	SONORK_ZeroMem(&ctrlData,sizeof(ctrlData));
}



// ----------------------------------------------------------------------------
// TSonorkClientServerProfile
// ----------------------------------------------------------------------------
#define SONORK_CLNTSVRPROF_CODEC_F_HAS_UTS	0x00010000
void
 TSonorkClientServerProfile::CODEC_WriteDataMem	(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(SONORK_CLNTSVRPROF_CODEC_F_HAS_UTS);
	CODEC.WriteDWN((DWORD*)&uts , SIZEOF_IN_DWORDS(uts) );
	CODEC.WriteDW(3);
	CODEC.Write(&sonork);
	CODEC.Write(&socks);
	CODEC.Write(&reserved);
}

void
 TSonorkClientServerProfile::CODEC_ReadDataMem	(TSonorkCodecReader& CODEC)
{
	DWORD	aux;
	if( CODEC.DataType() != CODEC_DataType() )
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW(&aux);
	if((aux&0xff)==0)
	{
		if( aux&SONORK_CLNTSVRPROF_CODEC_F_HAS_UTS)
		{
			CODEC.ReadDWN((DWORD*)&uts , SIZEOF_IN_DWORDS(uts) );
		}
		CODEC.Skip(sizeof(DWORD));
		CODEC.Read(&sonork);
		CODEC.Read(&socks);
		CODEC.Read(&reserved);
	}
}

DWORD
 TSonorkClientServerProfile::CODEC_DataSize(DWORD version)	const
{
	return sizeof(DWORD)*2
		+ sonork.CODEC_Size(version)
		+ socks.CODEC_Size(version)
		+ reserved.CODEC_Size(version)
		+ sizeof(uts);

}

void
 TSonorkClientServerProfile::Clear()
{
	sonork.Clear();
	socks.Clear();
	reserved.Clear();
	memset(&uts,0,sizeof(uts));
}


// ----------------------------------------------------------------------------
// TSonorkSysMsg
// ----------------------------------------------------------------------------

void
 TSonorkSysMsg::Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
	text.Clear();
}

void
 TSonorkSysMsg::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&text);
}
void
 TSonorkSysMsg::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD aux;
	if( CODEC.DataType() != CODEC_DataType() )
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW(&aux);
	aux&=0xfff;
	CODEC.ReadDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Skip(aux - sizeof(header));
	CODEC.Read(&text);
	
}
DWORD
 TSonorkSysMsg::CODEC_DataSize(DWORD version) const
{
	return 	  sizeof(DWORD)
			+ sizeof(header)
			+ text.CODEC_Size(version);
};


// ----------------------------------------------------------------------------
// TSonorkSimpleDataListAtom
// ----------------------------------------------------------------------------

void
 TSonorkSimpleDataListAtom::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW( DL->Items() );
	CODEC.WriteDW( DL->ItemSize() );
	CODEC.WriteDW( 0 );
	CODEC.WriteRaw( DL->w_ItemPtr(0) , DL->Items() * DL->ItemSize() );
}
void
 TSonorkSimpleDataListAtom::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD ci,mi,sz;
	CODEC.ReadDW( &mi );
	CODEC.ReadDW( &sz );
	if( sz != DL->ItemSize()
	|| (force_type_match && CODEC.DataType() != type) )
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
	}
	else
	{
		CODEC.Skip( sizeof(DWORD) );
		DL->PrepareFor( mi );
		for(ci=0; ci<mi && CODEC.CodecOk() ;ci++)
		{
			if(CODEC.RemainingSize()>=sz)
				DL->w_AddItem( CODEC.OffsetPtr() );
			CODEC.Skip( sz );
		}
	}

}
DWORD
 TSonorkSimpleDataListAtom::CODEC_DataSize(DWORD ) const
{
	return (sizeof(DWORD)*3) + (DL->Items() * DL->ItemSize());
}

DWORD
 TSonorkAtomQueue::SumAtomsCodecSize(DWORD codecVersion) const
{
	TSonorkListIterator I;
	TSonorkCodecAtom	*A;
	DWORD			rv=0;
	BeginEnum(I);
	while((A=EnumNextAtom(I))!=NULL)
		rv+=A->CODEC_Size(codecVersion);
	EndEnum(I);
	return rv;

}

void
 TSonorkAtomQueue::Clear()
{
	TSonorkCodecAtom* A;
	while( (A=RemoveFirstAtom()) != NULL )
		SONORK_MEM_DELETE(A);
};



// ----------------------------------------------------------------------------
// TSonorkWappData
// ----------------------------------------------------------------------------

void
 TSonorkWappData::Set(const TSonorkWappData&O)
{
	memcpy(&header,&O.header,sizeof(header));
	name.Set(O.name);
}
void
 TSonorkWappData::Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
	name.Clear();
}
DWORD
 TSonorkWappData::CODEC_DataSize(DWORD)	const
{
	return ::CODEC_Size(&name) + sizeof(header);
}

void
 TSonorkWappData::CODEC_WriteDataMem(TSonorkCodecWriter&CODEC) const
{
	CODEC.WriteDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&name);
}

void
 TSonorkWappData::CODEC_ReadDataMem(TSonorkCodecReader&CODEC)
{
	if( CODEC.DataType() != CODEC_DataType() )
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Read(&name);
}


// ----------------------------------------------------------------------------
// TSonorkGroup
// ----------------------------------------------------------------------------

void
 TSonorkGroup::Set(const TSonorkGroup&O)
{
	memcpy(&header,&O.header,sizeof(header));
	name.Set( O.name );
}
void
 TSonorkGroup::Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
	name.Clear();
}

DWORD
 TSonorkGroup::CODEC_DataSize(DWORD codecVersion)	const
{
	return sizeof(DWORD)
		+ sizeof(header)
		+ name.CODEC_Size(codecVersion);
}

void
 TSonorkGroup::CODEC_WriteDataMem(TSonorkCodecWriter&CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&name);
}
void
 TSonorkGroup::CODEC_ReadDataMem(TSonorkCodecReader&CODEC)
{
	DWORD	aux;
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Skip((aux&0xfff) - sizeof(header));
	CODEC.Read(&name);
}

// ----------------------------------------------------------------------------
// TSonorkMsg
// ----------------------------------------------------------------------------

TSonorkMsg::TSonorkMsg()
{
	SONORK_ZeroMem(&header,sizeof(header));
	text.header.flags=0;
}

void
 TSonorkMsg::Set(const TSonorkMsg& O)
{
	memcpy(&header,&O.header,sizeof(header));
	text.Set(O.text);
	data.Set(O.data);
}

void
 TSonorkMsg::Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
	ClearText();
	ClearData();
}

DWORD
 TSonorkMsg::CODEC_DataSize(DWORD codecVersion) const
{
	return  sizeof(DWORD)
		+	sizeof(header)
		+	text.CODEC_Size(codecVersion)
		+	data.CODEC_Size(codecVersion);
}

void
 TSonorkMsg::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN((DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&text);
	CODEC.Write(&data);
}
void
 TSonorkMsg::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	aux;
	if( CODEC.DataType() != CODEC_DataType() )
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW(&aux);
	aux&=0xfff;
	if( aux == sizeof(TSonorkOldMsgHeader) )
	{
		CODEC.ReadDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(TSonorkOldMsgHeader) );
		// Must clear new data
		header.target.Clear();
	}
	else
	{
		CODEC.ReadDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
		CODEC.Skip(aux-sizeof(header));
	}
	CODEC.Read(&text);
	CODEC.Read(&data);
}

// ----------------------------------------------------------------------------
// TSonorkUserData
// ----------------------------------------------------------------------------

#if defined(SONORK_CLIENT_BUILD)
TSonorkUserData::TSonorkUserData(SONORK_USER_INFO_LEVEL level)
{
	UINT sz;
	infoLevel=level;
	sz=GetUserInfoSize( false );
	userInfo=SONORK_MEM_ALLOC( TSonorkUserInfo3 , sz );
}
#else
TSonorkUserData::TSonorkUserData()
{
	infoLevel=SONORK_USER_INFO_LEVEL_3;
	userInfo=SONORK_MEM_ALLOC( TSonorkUserInfo3 , sizeof(TSonorkUserInfo3) );
}
#endif


TSonorkUserData::~TSonorkUserData()
{
	assert( userInfo !=NULL );
	SONORK_MEM_FREE(userInfo);
}

void
 TSonorkUserData::Set(const TSonorkUserData&O)
{
	UINT sz;
	SetUserInfoLevel( O.GetUserInfoLevel() , false );
	userId.Set(O.userId);
// USER SIZE CALCULATION
	if((sz = GetUserInfoSize( true ))!=0)
		memcpy( userInfo, O.userInfo, sz);

	alias.Set(O.alias);
	name.Set(O.name);
	email.Set(O.email);
	addr.Set(O.addr);
}
void
 TSonorkUserData::CopyUserInfo(const TSonorkUserInfo1* o_info,SONORK_USER_INFO_LEVEL o_level)
{
	DWORD	c_size;
	DWORD   o_size;
	o_size  = GetUserInfoSize( o_level , false );
	c_size  = GetUserInfoSize( false );
	if( c_size > o_size )
		c_size = o_size;
	memcpy(userInfo , o_info , c_size );
}

void
 TSonorkUserData::Clear(bool reset_info_level)
{
	if(reset_info_level)
		SetUserInfoLevel(SONORK_USER_INFO_LEVEL_0,false);
	else
		SONORK_ZeroMem(userInfo,GetUserInfoSize( false ));
	alias.Clear();
	name.Clear();
	email.Clear();
	addr.Clear();
}

DWORD
 TSonorkUserData::GetUserInfoSize(SONORK_USER_INFO_LEVEL p_level, BOOL for_codec)
{
	switch( p_level )
	{
		case SONORK_USER_INFO_LEVEL_0:
			return for_codec?0:sizeof(TSonorkUserInfo1);
		case SONORK_USER_INFO_LEVEL_1:
			return sizeof(TSonorkUserInfo1);
		case SONORK_USER_INFO_LEVEL_2:
			return sizeof(TSonorkUserInfo2);
		case SONORK_USER_INFO_LEVEL_3:
		default:
			return sizeof(TSonorkUserInfo3);
	}
}

DWORD
 TSonorkUserData::CODEC_DataSize(DWORD codecVersion) const
{
	if( codecVersion >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		return
			sizeof(DWORD)
		+	::CODEC_Size( &userId )
		+	::CODEC_Size( &alias  )
		+	::CODEC_Size( &name   )
		+	::CODEC_Size( &email  )
		+	addr.CODEC_Size(codecVersion)
		+	GetUserInfoSize( true );

	}
	else
	{
		return
			sizeof(DWORD)
		+	::CODEC_Size( &userId )
		+	::CODEC_Size( &alias  )
		+	::CODEC_Size( &name   )
		+	::CODEC_Size( &email  )
		+	::CODEC_UserAddrSize_obsolete( &addr   , true )
		+	GetUserInfoSize( true );
	}
}

#define SONORK_USER_CODEC_F_V15_ADDRESS		0x00100000
#define SONORK_USER_CODEC_SIZE_INFO_MASK	0x000fffff

void
 TSonorkUserData::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	DWORD	codec_flags;
	UINT	info_size;

	// We write the user info structure size
	//  because future versions may use larger structures
	//  which will be unknown to older versions;
	//  this stored size is used by ReadDataMem
	//  which reads the user info up to largest known structure size
	//  and then skips any remaining data

	info_size 	= GetUserInfoSize( true );
	codec_flags 	= ((info_size & 0xffff) << 4)
			| (infoLevel&0xf);

	if( CODEC.Version() >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		CODEC.WriteDW(codec_flags);
		CODEC.WriteDW2(&userId);
		CODEC.WriteUI(userInfo , infoLevel);
		CODEC.Write(&alias);
		CODEC.Write(&name);
		CODEC.Write(&email);
		CODEC.Write(&addr);
	}
	else
	{
		codec_flags|=SONORK_USER_CODEC_F_V15_ADDRESS;
		CODEC.WriteDW(codec_flags);
		CODEC.WriteDW2(&userId);
		CODEC.WriteUI( userInfo , infoLevel);
		CODEC.Write(&alias);
		CODEC.Write(&name);
		CODEC.Write(&email);
		CODEC.WriteUA_obsolete( &addr , true );
	}
}

void
 TSonorkUserData::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	codec_flags;
	UINT	sent_info_size;
	UINT	our_info_size;

	if( CODEC.DataType() != CODEC_DataType() )
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}

	CODEC.ReadDW(&codec_flags);	// udc_flags

	sent_info_size = (codec_flags>>4)&0xffff;

	SetUserInfoLevel( (SONORK_USER_INFO_LEVEL)((codec_flags)&0xf) , false );
	our_info_size = GetUserInfoSize( true );
	CODEC.ReadDW2(&userId);
	CODEC.ReadUI( userInfo , infoLevel );
	CODEC.Skip( sent_info_size - our_info_size );	// Skip remaining bytes
	CODEC.Read(&alias);
	CODEC.Read(&name);
	CODEC.Read(&email);

	if( CODEC.Version() >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		CODEC.Read(&addr);
	}
	else
	{
		CODEC.ReadUA_obsolete(&addr,codec_flags & SONORK_USER_CODEC_F_V15_ADDRESS);
	}
}

void
 TSonorkUserData::ClearUnusedFields()
{
	switch(GetUserInfoLevel())
	{
		case SONORK_USER_INFO_LEVEL_0:
			break;
		case SONORK_USER_INFO_LEVEL_1:
			((TSonorkUserInfo1*)userInfo)->ClearUnusedFields();
			break;
		case SONORK_USER_INFO_LEVEL_2:
			((TSonorkUserInfo2*)userInfo)->ClearUnusedFields();
			break;
		case SONORK_USER_INFO_LEVEL_3:
		default:
			((TSonorkUserInfo3*)userInfo)->ClearUnusedFields();
			break;
	}
}


// --------------------------------------
// TSonorkUserData::SetUdcFlags(UDC_flags,preserve_data)
// Sets the UDC (User Data Control) flags.
//  The <UDC_flags> determine the type the structure pointed to
//   by <user_info> and it will be one of the TSonorkUserInfo1,TSonorkUserInfo2,..
//   structures.
//  <preserve_data>
//  Tells the function whether it should try to preserve
//   the data in the structure pointed by the current <user_info> pointer.
//  If the current <user_info> pointer is NULL (no current data exists)
//   or the new structure size is zero (no data), the parameter is ignored
//   because there is no area from/into where to store data.

void
 TSonorkUserData::SetUserInfoLevel(SONORK_USER_INFO_LEVEL new_level,bool preserve_data)
{
#if defined(SONORK_CLIENT_BUILD)
	UINT 	old_size,new_size;

	// GetUserInfoSize() returns the size of the structure
	// pointed by <user_info> and is determined by <udc_flags>
	// The size of the structure will be the size of one of the
	// TSonorkUserInfoX structures

	if( new_level > SONORK_USER_INFO_LEVEL_3)new_level=SONORK_USER_INFO_LEVEL_3;

	if( new_level == infoLevel )return;

	// Get current size
	old_size	= GetUserInfoSize( false );

	// Set new level
	infoLevel	= new_level;

	// Get new size
	new_size	= GetUserInfoSize( false );

	// If new size and old size are not the same,
	// or we don't have the user_info pointer,
	// we need to reallocate the user_info structure
	if( new_size != old_size )
	{
		TSonorkUserInfo3*old_info;

		// Save the old pointer
		old_info = userInfo;
		userInfo =SONORK_MEM_ALLOC( TSonorkUserInfo3 , new_size );
		if( old_info!= NULL )
		{
			// If a) There existed data in this structure before the change
			// and b) Our user info level is not zero
			// and c) The data should be preserved
			// we copy all available data from the old structure
			if( preserve_data )
			{
				if( old_size > new_size )
					old_size = new_size;
				memcpy(userInfo , old_info , old_size);
				ClearUnusedFields();
			}
			// we no longer need the old pointer, delete it
			SONORK_MEM_FREE(old_info);
		}
		else
		{
			SONORK_ZeroMem(userInfo,new_size);
		}
	}
#else
	if( new_level > SONORK_USER_INFO_LEVEL_3)new_level=SONORK_USER_INFO_LEVEL_3;
	infoLevel = new_level;
	// No effect code, just to make the
	// compiler warning "parameter not used" go away
	preserve_data;
#endif
}
void
 TSonorkUserData::Set(const TSonorkUserInfo1*UI,SONORK_USER_INFO_LEVEL new_level)
{
	UINT sz;
	if( new_level != infoLevel )
	{
#if defined(SONORK_CLIENT_BUILD)
		SetUserInfoLevel( new_level , false);
#else
		infoLevel = new_level;
#endif
	}
	if((sz=GetUserInfoSize( true ))!=0)
		memcpy(userInfo,UI,sz);
}

void
 TSonorkUserData::GetLocus(TSonorkLocus1*locus)   const
{
	locus->userId.Set(userId);
	locus->sid.Set(addr.header.sid);
}


void
 TSonorkUserData::GetLocus(TSonorkLocusAtom* A)   const
{
	GetLocus(&A->userLocusEx);
	A->userLocusEx.utsAddr.Set(addr.utsAddr);
	A->userLocusEx.hostAddr.Set(addr.hostAddr);
	A->userLocusEx.sidFlags.Set(addr.header.sidFlags);
	A->userLocusEx.region.Set(userInfo->region);
}

void
 TSonorkUserData::GetUserHandle(TSonorkUserHandle* H) const
{
	GetLocus(H);
	H->utsLinkId=0;
}


char*
 TSonorkUserData::CODEC_GetTextView(char*buffer,DWORD size) const
{
	if(size<SONORK_USER_ALIAS_MAX_SIZE + SONORK_ID_MAX_STR_SIZE +8)
		*buffer=0;
	else
	{
		sprintf(buffer
			,"%u.%u %s"
			,userId.v[0]
			,userId.v[1]
			,alias.CStr());
	}
	return buffer;
}


// ----------------------------------------------------------------------------
// TSonorkError
// ----------------------------------------------------------------------------

const char *
 TSonorkError::ResultName() const
{
	return SONORK_ResultName(Result());
}

char*
 TSonorkError::CODEC_GetTextView(char*buffer,DWORD size) const
{
	UINT l;
	if(Result()==SONORK_RESULT_OK || size<32)
	{
		*buffer=0;
	}
	else
	{
		l=sprintf(buffer
			,"%s/%x"
			,ResultName()
			,Code() );
		if(size >= l + Text().Length() + 2)
			sprintf(buffer+l," %s",Text().CStr());
	}
	return buffer;

}


void
 TSonorkError::SetExtendedInfo(SONORK_C_CSTR p_str,DWORD p_code)
{
	text.Set(p_str);
	code=p_code;
#if defined(SONORK_CLIENT_BUILD)
	local=true;
#endif
}

#if !defined(SONORK_IPC_BUILD)

void
 TSonorkError::SetSys(SONORK_RESULT p_result,SONORK_SYS_STRING p_index,DWORD p_code)
{
	result	= p_result;
	code    = p_code;
	if(p_index != GSS_NULL)
	{
		text.SetBufferSize(48);
		sprintf(text.Buffer(),"!GU!%s",SONORK_SysIndexToLexeme(p_index));
	}
	else
	{
		text.Clear();
	}
#if defined(SONORK_CLIENT_BUILD)
	local=true;
#endif
}

void
 TSonorkError::SetSysExtInfo(SONORK_SYS_STRING p_index,DWORD p_code)
{
	SetSys(result, p_index, p_code);
}

#endif

SONORK_RESULT
 TSonorkError::SetOk()
{
#if defined(SONORK_SERVER_BUILD)
	return Set(SONORK_RESULT_OK,csNULL,0);
#else
	return Set(SONORK_RESULT_OK,csNULL,0,true);
#endif
}

SONORK_RESULT
	TSonorkError::Set(const TSonorkError&O)
{
	result=O.result;
	code=O.code;
	text.Set(O.text);
#if defined(SONORK_CLIENT_BUILD)
	local=O.local;
#endif
	return result;
}

#if defined(SONORK_SERVER_BUILD)
SONORK_RESULT
 TSonorkError::Set(SONORK_RESULT r,SONORK_C_CSTR s,DWORD c)
#else
SONORK_RESULT
 TSonorkError::Set(SONORK_RESULT r,SONORK_C_CSTR s,DWORD c, bool l)
#endif
{
	result=r;
	code=c;
	text.Set(s);
#if !defined(SONORK_SERVER_BUILD)
	local=l;
#endif
	return result;
}
DWORD
 TSonorkError::CODEC_DataSize(DWORD) const
{
	if(result!=SONORK_RESULT_OK)
		return SIZEOF_DWORD*2 + :: CODEC_Size(&text);
	else
		return SIZEOF_DWORD;
}

void
 TSonorkError::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(result);
	if(result!=SONORK_RESULT_OK)
	{
		CODEC.WriteDW(code);
		CODEC.Write(&text);
	}
}
void
 TSonorkError::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD aux;
	CODEC.ReadDW(&aux);
	if(aux==SONORK_RESULT_OK)
	{
		SetOk();
	}
	else
	{
		result=(SONORK_RESULT)aux;
		CODEC.ReadDW(&code);
		CODEC.Read(&text);
	}
}

// ----------------------------------------------------------------------------
// TSonorkDynData
// ----------------------------------------------------------------------------

TSonorkDynData::TSonorkDynData(SONORK_ATOM_TYPE type)
{
	buffer=NULL;
	data_type=type;
	block_size=1024;
	buffer_size=data_size=0;
}
UINT
 TSonorkDynData::GenerateSignature()
{
	return Sonork_GenerateSignature(Buffer(),DataSize());
}


void
 TSonorkDynData::Set(const TSonorkDynData&O)
{
	if(buffer)SONORK_MEM_FREE(buffer);

	data_type=O.data_type;
	if(O.DataSize())
	{
		data_size=buffer_size=O.DataSize();
		buffer=SONORK_MEM_ALLOC(BYTE,data_size);
		memcpy(buffer,O.buffer,data_size);
	}
	else
	{
		buffer=NULL;
		data_size=buffer_size=0;
	}

}
void
 TSonorkDynData::Assign(BYTE*ptr,UINT sz)
{
	if(buffer)SONORK_MEM_FREE(buffer);
	buffer=ptr;
	if(buffer)
		data_size=buffer_size=sz;
	else
		data_size=buffer_size=0;
}
void
 TSonorkDynData::SetRaw(const void*p_data,UINT p_size,SONORK_ATOM_TYPE p_type)
{
	SetDataSize( p_size , true );
	if(p_size)
		memcpy( buffer , p_data, p_size );
	data_type=p_type;

}
void
 TSonorkDynData::SetDWN(const DWORD*ptr,UINT count)
{
	SetDataSize( SIZEOF_DWORD * count , true );
	if(count)
		CODEC_WRITE_DWN( ptr , buffer , count);
}

void
 TSonorkDynData::AppendStr(SONORK_C_CSTR string, BOOL append_null)
{
	if(string)
		Append(string,strlen(string)+(append_null?1:0));
}

void
 TSonorkDynData::SetStr(SONORK_C_CSTR string)
{
	int l=string?strlen(string):0;
	SetDataSize( l+1 , true );
	if(l)
		memcpy(buffer,string,l+1);
	else
		*buffer=0;
	data_type=SONORK_ATOM_CSTR;
}

void
 TSonorkDynData::CODEC_WriteDataMem(TSonorkCodecWriter&CODEC) const
{
	if(DataSize())
		CODEC.WriteRaw( buffer ,DataSize());
}

void
 TSonorkDynData::CODEC_ReadDataMem(TSonorkCodecReader&CODEC)
{
	UINT codec_size;
	data_type=CODEC.DataType();
	codec_size=CODEC.RemainingSize();
	if(codec_size)
	{
		SetBufferSize(codec_size,false);
		CODEC.ReadRaw(buffer,codec_size);
	}
	data_size=codec_size;

}

void
 TSonorkDynData::SetBlockSize(UINT size)
{
	if(size<256)block_size=256;
	else
	if(size>8096*2)block_size=8096*2;
	else
		block_size=size;
}

void
 TSonorkDynData::Clear()
{
	data_type=SONORK_ATOM_NONE;
	if(buffer != NULL)
	{
		SONORK_MEM_FREE(buffer);
		buffer=NULL;
	}
	buffer_size=data_size=0;
}

void
 TSonorkDynData::SetDataSize(UINT p_size, bool adjust_buffer) // Always discards data
{
	if( data_size != p_size )
	{
		if(adjust_buffer)
			SetBufferSize(p_size,false);
		data_size=p_size;
	}
}
void
 TSonorkDynData::SetBufferSize(UINT p_size,bool preserve_data)
{
	if( p_size != buffer_size )
	{
		void *old_buffer;
		old_buffer=buffer;
		buffer_size=p_size;
		buffer=SONORK_MEM_ALLOC(BYTE,buffer_size + 4);
		if(old_buffer)
		{
			if(preserve_data)
			{
				if(buffer_size<data_size)
					data_size=buffer_size;
				if(data_size)
				{
					memcpy(buffer,old_buffer,data_size);
				}
			}
			else
				data_size=0;
			SONORK_MEM_FREE(old_buffer);
		}
		else
			data_size =0;
	}
}
void
 TSonorkDynData::Append(const void*p_data,UINT p_size)
{
	if(data_size+p_size>buffer_size)
	{
		UINT blocks=((data_size+p_size)-buffer_size)/BlockSize()+1;
		UINT saved_data_size=data_size;
		SetBufferSize(BufferSize()+blocks*BlockSize(),true);
		data_size=saved_data_size;
	}
	memcpy(buffer+data_size,p_data,p_size);
	data_size+=p_size;
}



// ----------------------------------------------------------------------------
// TSonorkText
// ----------------------------------------------------------------------------

void
 TSonorkText::SetStr(DWORD flags,SONORK_C_CSTR str)
{
	header.flags = flags;
	string.Set(str);
}
void
 TSonorkText::SetString(DWORD flags,const TSonorkDynString& S)
{
	header.flags=flags;
	string.Set(S);
}

void
 TSonorkText::Clear()
{
	header.flags=0;
	header.region.Clear();
	string.Clear();
}

void
 TSonorkText::Set(const TSonorkText&O)
{
	header.flags=O.header.flags;
	header.region.Set(O.header.region);
	string.Set(O.string);
}
void
 TSonorkText::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN((DWORD*)&header, SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&string);
}

void
 TSonorkText::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD aux;
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN((DWORD*)&header, SIZEOF_IN_DWORDS(header) );
	CODEC.Skip((aux&0xfff) - sizeof(header));
	CODEC.Read(&string);
}

DWORD
 TSonorkText::CODEC_DataSize(DWORD codecVersion) const
{
	return	sizeof(DWORD)
		+	sizeof(header)
		+	string.CODEC_Size(codecVersion);
}

// ----------------------------------------------------------------------------
// TSonorkServiceData
// ----------------------------------------------------------------------------
#define SONORK_SERVER_CODEC_F_EXTENDED_CODEC_1	0x00010000
void
 TSonorkServiceData::Set(const TSonorkServiceData&O)
{
	memcpy(&serverAddr,&O.serverAddr,sizeof(serverAddr));
	notes.Set(O.notes);
}
void
 TSonorkServiceData::Clear()
{
	SONORK_ZeroMem( &serverAddr, sizeof(serverAddr) );
	notes.Clear();
}


DWORD
 TSonorkServiceData::CODEC_DataSize(DWORD codecVersion) const
{
	DWORD	aux ;

	if( codecVersion >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		aux = sizeof(DWORD)
			+ sizeof(TSonorkNewUserServerHeader);

		aux+=::CODEC_Size(&serverAddr.hostAddr);
	}
	else
	{
		aux = sizeof(DWORD)
			+ sizeof(TSonorkOldUserServerHeader);
	}
	aux+=::CODEC_Size(&serverAddr.utsAddr);
	aux+=::CODEC_Size(&notes);
	return aux;
}

void
 TSonorkServiceData::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	if( CODEC.Version() >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		CODEC.WriteDW(sizeof(TSonorkNewUserServerHeader));
		CODEC.WriteDWN((DWORD*)&serverAddr, SIZEOF_IN_DWORDS(TSonorkNewUserServerHeader) );
		CODEC.WritePA1(&serverAddr.utsAddr);
		CODEC.WritePA1(&serverAddr.hostAddr);
	}
	else
	{
		CODEC.WriteDW(sizeof(TSonorkOldUserServerHeader));
		CODEC.WriteDWN((DWORD*)&serverAddr, SIZEOF_IN_DWORDS(TSonorkOldUserServerHeader) );
		CODEC.WritePA1(&serverAddr.utsAddr);
	}
	CODEC.Write(&notes);
}

void
 TSonorkServiceData::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD aux;
	CODEC.ReadDW(&aux);
	if( CODEC.Version() >= SONORK_EXTENDED_CODEC_VERSION_1 )
	{
		CODEC.ReadDWN((DWORD*)&serverAddr,SIZEOF_IN_DWORDS(TSonorkNewUserServerHeader));
		CODEC.Skip((aux&0xfff) - sizeof(TSonorkNewUserServerHeader));
		CODEC.ReadPA1(&serverAddr.utsAddr);
		CODEC.ReadPA1(&serverAddr.hostAddr);
	}
	else
	{
		CODEC.ReadDWN((DWORD*)&serverAddr,SIZEOF_IN_DWORDS(TSonorkOldUserServerHeader));
		CODEC.Skip((aux&0xfff) - sizeof(TSonorkOldUserServerHeader));
		CODEC.ReadPA1(&serverAddr.utsAddr);
		serverAddr.hostAddr.Set(serverAddr.utsAddr);
	}
	CODEC.Read(&notes);
}


// ----------------------------------------------------------------------------
// TSonorkDynString
// ----------------------------------------------------------------------------

TSonorkDynString::TSonorkDynString(SONORK_C_CSTR str)
{
	flags=0;s.c=NULL;Set(str,true);
}
TSonorkDynString::TSonorkDynString(SONORK_W_CSTR str)
{
	flags=0;s.c=NULL;Set(str,true);
}
TSonorkDynString::TSonorkDynString(TSonorkDynString&S)
{
	s.c=NULL;
	Set(S);
}
char* TSonorkDynString::CODEC_GetTextView(char*buffer,DWORD size) const
{
	Get(buffer,size);
	return buffer;

}
SONORK_C_CSTR
 TSonorkDynString::CStr() const
{
	if(IsNull())return "";
	if(Type()!=SONORK_DYN_STRING_TYPE_C)
		return "";
	return s.c;
}
SONORK_W_CSTR
 TSonorkDynString::WStr() const
{
	static SONORK_W_CHAR zero=0;
	if(IsNull())return &zero;
	if(Type()!=SONORK_DYN_STRING_TYPE_W)
		return &zero;
	return s.w;
}

UINT
 TSonorkDynString::CharByteSize() const
{
	if(Type()==SONORK_DYN_STRING_TYPE_C)
		return sizeof(SONORK_C_CHAR);
	else
	if(Type()==SONORK_DYN_STRING_TYPE_W)
		return sizeof(SONORK_W_CHAR);
	else
		return 0;
}

bool
 TSonorkDynString::operator==(TSonorkDynString&S)
{
	if(Type()==S.Type())
	{
		if(s.c&&S.s.c)
		{
			assert(Type()==SONORK_DYN_STRING_TYPE_C);
			return !SONORK_StrNoCaseCmp(s.c,S.s.c);
		}
	}
    return false;

}

bool
 TSonorkDynString::operator==(SONORK_C_CSTR      str)
{
	if(Type()==SONORK_DYN_STRING_TYPE_C)
	{
		return !SONORK_StrNoCaseCmp(s.c,str);
	}
	return false;

}
void
 TSonorkDynString::Clear()
{
	if(s.c)
	{
		SONORK_MEM_FREE(s.c);
		s.c=NULL;
	}
	flags=0;
}
void
 TSonorkDynString::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	DWORD 	aux;
	UINT 	w_str_len;
	UINT	w_char_size;
	UINT 	w_bytes;
	UINT	buffer_size;

	buffer_size=CODEC.RemainingSize();
	if( buffer_size < SIZEOF_DWORD )
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	buffer_size-=SIZEOF_DWORD;
	w_char_size =CharByteSize();
	if(!w_char_size)
		w_str_len=0;
	else
		w_str_len=buffer_size/w_char_size;
	if(w_str_len>Length())
		w_str_len=Length();

	aux=(Type()|w_str_len);
	CODEC.WriteDW(aux);
	w_bytes=w_str_len*w_char_size;
	if(w_bytes)CODEC.WriteRaw(s.c,w_bytes);
}

void
 TSonorkDynString::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD 	aux;
	UINT 	r_length;
	UINT  	b_length;
	UINT	r_char_size;
	UINT  	r_bytes;
	UINT 	buffer_size;

	buffer_size=CODEC.RemainingSize();
	if(CODEC.DataType() != SONORK_ATOM_DYN_STRING ||  buffer_size < SIZEOF_DWORD)
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	buffer_size -= SIZEOF_DWORD;
	CODEC.ReadDW(&aux);
	flags=aux;
	r_char_size=CharByteSize();
	if(!r_char_size)
	{
		s.c=NULL;
	}
	else
	{
		r_length=Length();
		b_length=buffer_size/r_char_size;
		if(r_length>b_length)
		{
			r_length=b_length;
			flags&=~SONORK_DYN_STRING_FM_LENGTH;
			flags|=(r_length&SONORK_DYN_STRING_FM_LENGTH);
		}
		r_bytes	=r_length*r_char_size;
		s.c   =SONORK_MEM_ALLOC(SONORK_C_CHAR,(r_bytes)+sizeof(SONORK_W_CHAR));
		if(r_bytes)CODEC.ReadRaw(s.c,r_bytes);
		*(SONORK_W_CHAR*)(s.c+r_bytes)=0;
	}
}

SONORK_C_CSTR
 TSonorkDynString::ToCStr()
{
	if(Type()!=SONORK_DYN_STRING_TYPE_C)
	{
		if(!IsNull()&&Length())
		{
			SONORK_W_STR old_s=s.w;
			SONORK_C_STR new_s;
			UINT     new_len;
			new_len=Get(&new_s);
			if(old_s)SONORK_MEM_FREE(old_s);
			s.c=new_s;
			flags=SONORK_DYN_STRING_TYPE_C|(new_len&SONORK_DYN_STRING_FM_LENGTH);
		}
		else
			flags=SONORK_DYN_STRING_TYPE_C;

	}
	return CStr();

}

SONORK_W_CSTR
 TSonorkDynString::ToWStr()
{
	if(Type()!=SONORK_DYN_STRING_TYPE_W)
	{
		if(!IsNull()&&Length())
		{
			SONORK_C_STR old_s=s.c;
			SONORK_W_STR new_s;
			UINT     new_len;
			new_len=Get(&new_s);
			if(old_s)SONORK_MEM_FREE(old_s);
			s.w=new_s;
			flags=SONORK_DYN_STRING_TYPE_W|(new_len&SONORK_DYN_STRING_FM_LENGTH);
		}
		else
			flags=SONORK_DYN_STRING_TYPE_W;
	}
    return WStr();
}

void
 TSonorkDynString::Set(const TSonorkDynString& S)
{
	Clear();
	if(!S.IsNull())
	{
		UINT byte_size;
		flags=S.flags;
		byte_size=S.StringByteSize();
		s.c=SONORK_MEM_ALLOC(SONORK_C_CHAR,byte_size+sizeof(SONORK_W_CHAR));
		if(byte_size&&S.s.c)memcpy(s.c,S.s.c,byte_size);
		*(SONORK_W_CHAR*)(s.c+byte_size)=0;
	}
}

void
 TSonorkDynString::Set(SONORK_C_CSTR str,bool do_a_copy)
{
	int l;
	Clear();
	if(do_a_copy)
	{
		if(str)
			s.c=SONORK_CStr(str);
		else
			s.c=SONORK_CStr("");
	}
	else
		s.c=(SONORK_C_STR)str;
	l=s.c?SONORK_StrLen(s.c):0;
	flags=SONORK_DYN_STRING_TYPE_C|(l&SONORK_DYN_STRING_FM_LENGTH);

}

void
 TSonorkDynString::Set(SONORK_W_CSTR str,bool do_a_copy)
{
	int l;
	Clear();
	if(do_a_copy)
	{
		if(str)
			s.w=SONORK_WStr(str);
		else
			s.w=SONORK_WStr("");
	}
	else
		s.w=(SONORK_W_STR)str;
	l=s.w?SONORK_StrLen(s.w):0;
	flags=SONORK_DYN_STRING_TYPE_W|(l&SONORK_DYN_STRING_FM_LENGTH);
}
UINT
 TSonorkDynString::Get(SONORK_C_STR*buff) const
{
	UINT buff_length=Length()+1;
	*buff=SONORK_MEM_ALLOC(SONORK_C_CHAR,buff_length*sizeof(SONORK_C_CHAR));
	return Get(*buff,buff_length);
}
UINT
 TSonorkDynString::Get(SONORK_W_STR*buff) const
{
	UINT buff_length=Length()+1;
	*buff=SONORK_MEM_ALLOC(SONORK_W_CHAR,buff_length*sizeof(SONORK_W_CHAR));
	return Get(*buff,buff_length);
}

UINT TSonorkDynString::Get(SONORK_C_STR buff,UINT buff_length) const
{
	if(Type()==SONORK_DYN_STRING_TYPE_C)
		return SONORK_StrCopy(buff,buff_length,s.c,Length());
	else
	if(Type()==SONORK_DYN_STRING_TYPE_W)
		return SONORK_StrCopy(buff,buff_length,s.w,Length());
	else
	{
		if(buff)*buff=(SONORK_C_CHAR)0;
		return 0;
	}
}

UINT
 TSonorkDynString::Get(SONORK_W_STR buff,UINT buff_length) const
{
	if(Type()==SONORK_DYN_STRING_TYPE_C)
		return SONORK_StrCopy(buff,buff_length,s.c,Length());
	else
	if(Type()==SONORK_DYN_STRING_TYPE_W)
		return SONORK_StrCopy(buff,buff_length,s.w,Length());
	else
	{
		if(buff)
		*buff=(SONORK_W_CHAR)0;
		return 0;
	}
}

void
 TSonorkDynString::CutAt(UINT sz)
{
	if(!sz)
		Clear();
	else
	if(Length() > sz )
	{
		// We know s.c and s.w are not null because
		// Length() is not zero (above: Length()>sz and sz!=0)
		if(Type()==SONORK_DYN_STRING_TYPE_C)
		{
			SONORK_C_STR old_s=s.c;
			s.c=SONORK_CStr( sz+1 );

			memcpy(s.c,old_s,sz*sizeof(SONORK_C_CHAR));
			*(s.c+sz)=0;
			SONORK_MEM_FREE(old_s);
			flags=SONORK_DYN_STRING_TYPE_C|(sz&SONORK_DYN_STRING_FM_LENGTH);
		}
		else
		if(Type()==SONORK_DYN_STRING_TYPE_W)
		{
			SONORK_W_STR old_w=s.w;
			s.w=SONORK_WStr( sz+1 );

			memcpy(s.w,old_w,sz*sizeof(SONORK_W_CHAR));
			*(s.w+sz)=0;
			SONORK_MEM_FREE(old_w);
			flags=SONORK_DYN_STRING_TYPE_W|(sz&SONORK_DYN_STRING_FM_LENGTH);

		}
	}
}

void
 TSonorkDynString::Append(SONORK_C_CSTR str1, SONORK_C_CSTR str2)
{
	int l1,l2,nl;
	assert(Type()==SONORK_DYN_STRING_TYPE_C||Type()==SONORK_DYN_STRING_TYPE_NULL);

	if(!SONORK_IsEmptyStr(str1))
		l1=strlen(str1);
	else
		l1=0;

	if(!SONORK_IsEmptyStr(str2))
		l2=strlen(str2);
	else
		l2=0;

	nl=l1+l2;
	if(nl)
	{
		char *new_str,*append_point;
		nl+=Length();
		new_str=SONORK_CStr(nl+1);
		if(Length())
			strcpy(new_str,CStr());
		else
			*new_str=0;
		append_point=new_str+Length();
		if(l1)strcat(append_point,str1);
		if(l2)strcat(append_point,str2);

		Clear();
		s.c=(SONORK_C_STR)new_str;
		flags=SONORK_DYN_STRING_TYPE_C|(nl&SONORK_DYN_STRING_FM_LENGTH);
	}
}

// ----------------------------------------------------------------------------
// TSonorkUserDataNotes
// ----------------------------------------------------------------------------

DWORD
 TSonorkUserDataNotes::CODEC_Size(DWORD codecFlags, DWORD codecVersion) const
{
	return ::CODEC_Size(this,codecFlags, codecVersion);
}

void
 TSonorkUserDataNotes::Set( const TSonorkUserDataNotes& O)
{
	userData.Set(O.userData);
	password.Set(O.password);
	auth.Set(O.auth);
	notes.Set(O.notes);

}

void
 TSonorkUserDataNotes::Clear()
{
	userData.Clear();
	password.Clear();
	auth.Clear();
	notes.Clear();
}

// ----------------------------------------------------------------------------
// TSonorkTrackerRoom
// ----------------------------------------------------------------------------

void
 TSonorkTrackerRoom::Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
	name.Clear();
	text.Clear();
	data.Clear();
}
void
 TSonorkTrackerRoom::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&name);
	CODEC.Write(&text);
	CODEC.Write(&data);
}
void
 TSonorkTrackerRoom::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	aux;
	if( CODEC.DataType() != CODEC_DataType())
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	aux&=0xfff;
	CODEC.Skip(aux-sizeof(header));
	CODEC.Read(&name);
	CODEC.Read(&text);
	CODEC.Read(&data);
}

DWORD
 TSonorkTrackerRoom::CODEC_DataSize(DWORD codecVersion) const
{
	return sizeof(DWORD)
		+sizeof(header)
		+name.CODEC_Size(codecVersion)
		+text.CODEC_Size(codecVersion)
		+data.CODEC_Size(codecVersion);

}


// ----------------------------------------------------------------------------
// TSonorkTrackerData
// ----------------------------------------------------------------------------

void
 TSonorkTrackerData::Clear()
{
	SONORK_ZeroMem(&header,sizeof(header));
	text.Clear();
	data.Clear();
}
void
 TSonorkTrackerData::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.WriteDW(sizeof(header));
	CODEC.WriteDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	CODEC.Write(&text);
	CODEC.Write(&data);
}
void
 TSonorkTrackerData::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	DWORD	aux;

	if( CODEC.DataType() != CODEC_DataType())
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.ReadDW(&aux);
	CODEC.ReadDWN( (DWORD*)&header , SIZEOF_IN_DWORDS(header) );
	aux&=0xfff;
	CODEC.Skip(aux-sizeof(header));
	CODEC.Read(&text);
	CODEC.Read(&data);
}

DWORD
 TSonorkTrackerData::CODEC_DataSize(DWORD codecVersion) const
{
	return sizeof(DWORD)
		+sizeof(header)
		+text.CODEC_Size(codecVersion)
		+data.CODEC_Size(codecVersion);

}


// ----------------------------------------------------------------------------
// TSonorkTrackerMember
// ----------------------------------------------------------------------------

void
 TSonorkTrackerMember::Clear()
{
	trackData.Clear();
	userData.Clear();
}
void
 TSonorkTrackerMember::CODEC_WriteDataMem(TSonorkCodecWriter& CODEC) const
{
	CODEC.Write( &userData );
	CODEC.Write( &trackData);
}
void
 TSonorkTrackerMember::CODEC_ReadDataMem(TSonorkCodecReader& CODEC)
{
	if( CODEC.DataType() != CODEC_DataType())
	{
		CODEC.SetBadCodecError( __FILE__ , SONORK_MODULE_LINE );
		return;
	}
	CODEC.Read( &userData );
	CODEC.Read( &trackData);
}

DWORD
 TSonorkTrackerMember::CODEC_DataSize(DWORD codecVersion) const
{
	return   userData.CODEC_Size(codecVersion)
		+trackData.CODEC_Size(codecVersion);

}

#endif // #if SONORK_CODEC_LEVEL>5



