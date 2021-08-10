//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      Common.h
//
//  Description:
//      Macros that wrap calling IClusCfgCallback::SendStatusReport.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
//  SendStatusReport Logging Macros
//
//  The following macros are used to simplify the usage of the
//  SendStatusReport function and tidy up the code by removing these often
//  used code patterns.
//
//////////////////////////////////////////////////////////////////////////////
#define LOG_STATUS_REPORT( _pwsz_, _hr_ ) \
    HrSendStatusReport( \
                          TASKID_Major_Update_Progress \
                        , TASKID_Major_Server_Log \
                        , 1 \
                        , 1 \
                        , 1 \
                        , _hr_\
                        , _pwsz_ \
                        , (UINT)NULL \
                        )

#define LOG_STATUS_REPORT_MINOR( _minor_, _pwsz_, _hr_ ) \
    HrSendStatusReport( \
                          TASKID_Major_Server_Log \
                        , _minor_ \
                        , 1 \
                        , 1 \
                        , 1 \
                        , _hr_ \
                        , _pwsz_ \
                        , (UINT)NULL \
                        )

#define LOG_STATUS_REPORT_MINOR_STRING( _minor_, _pwszFormat_, _arg0_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( _pwszFormat_, &_bstrMsg_, _arg0_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              TASKID_Major_Server_Log \
                            , _minor_ \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_ \
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , (UINT) 0 \
                            ); \
        if ( FAILED( _hrTemp_ ) && SUCCEEDED( _hr_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define LOG_STATUS_REPORT_STRING( _pwszFormat_, _arg0_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( _pwszFormat_, &_bstrMsg_, _arg0_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              TASKID_Major_Update_Progress \
                            , TASKID_Major_Server_Log \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_ \
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , (UINT) 0 \
                            ); \
        if ( FAILED( _hrTemp_ ) && SUCCEEDED( _hr_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define LOG_STATUS_REPORT_STRING2( _pwszFormat_, _arg0_, _arg1_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( _pwszFormat_, &_bstrMsg_, _arg0_, _arg1_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              TASKID_Major_Update_Progress \
                            , TASKID_Major_Server_Log \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_\
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , (UINT) 0 \
                            ); \
        if ( FAILED( _hrTemp_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define LOG_STATUS_REPORT_STRING3( _pwszFormat_, _arg0_, _arg1_, _arg2_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( _pwszFormat_, &_bstrMsg_, _arg0_, _arg1_, _arg2_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              TASKID_Major_Update_Progress \
                            , TASKID_Major_Server_Log \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_\
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , (UINT) 0 \
                            ); \
        if ( FAILED( _hrTemp_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define LOG_STATUS_REPORT_STRING4( _pwszFormat_, _arg0_, _arg1_, _arg2_, _arg3_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( _pwszFormat_, &_bstrMsg_, _arg0_, _arg1_, _arg2_, _arg3_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              TASKID_Major_Update_Progress \
                            , TASKID_Major_Server_Log \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_\
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , (UINT) 0 \
                            ); \
        if ( FAILED( _hrTemp_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define STATUS_REPORT_REF( _major_, _minor_, _idsMsg_, _idsRef_, _hr_ ) \
    HrSendStatusReport( \
                      _major_ \
                    , _minor_ \
                    , 1 \
                    , 1 \
                    , 1 \
                    , _hr_ \
                    , (DWORD) _idsMsg_ \
                    , (DWORD) _idsRef_ \
                    )

#define STATUS_REPORT_STRING( _major_, _minor_, _idsFormat_, _arg0_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( NULL, _idsFormat_, &_bstrMsg_, _arg0_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              _major_ \
                            , _minor_ \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_ \
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , (UINT)0 \
                            , (UINT)0 \
                            ); \
        if ( FAILED( _hrTemp_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define STATUS_REPORT_STRING2( _major_, _minor_, _idsFormat_, _arg0_, _arg1_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( NULL, _idsFormat_, &_bstrMsg_, _arg0_, _arg1_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              _major_ \
                            , _minor_ \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_ \
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , (UINT)0 \
                            , (UINT)0 \
                            ); \
        if ( FAILED( _hrTemp_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define STATUS_REPORT_STRING_REF( _major_, _minor_, _idsFormat_, _arg0_, _idsRef_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( NULL, _idsFormat_, &_bstrMsg_, _arg0_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              _major_ \
                            , _minor_ \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_ \
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , _idsRef_ \
                            , NULL \
                            ); \
        if ( FAILED( _hrTemp_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define STATUS_REPORT_STRING2_REF( _major_, _minor_, _idsFormat_, _arg0_, _arg1_, _idsRef_, _hr_ ) \
    { \
        BSTR    _bstrMsg_ = NULL; \
        HRESULT _hrTemp_; \
        \
        _hrTemp_ = HrFormatStringIntoBSTR( NULL, _idsFormat_, &_bstrMsg_, _arg0_, _arg1_ ); \
        _hrTemp_ = HrSendStatusReport( \
                              _major_ \
                            , _minor_ \
                            , 1 \
                            , 1 \
                            , 1 \
                            , _hr_ \
                            , _hrTemp_ == S_OK ? _bstrMsg_ : L"The description for this entry could not be located." \
                            , _idsRef_ \
                            , NULL \
                            ); \
        if ( FAILED( _hrTemp_ ) ) \
        { \
            _hr_ = _hrTemp_; \
        } \
        \
        SysFreeString( _bstrMsg_ ); \
    }

#define STATUS_REPORT( _major_, _minor_, _uid_, _hr_ ) \
    HrSendStatusReport( \
                          _major_ \
                        , _minor_ \
                        , 1 \
                        , 1 \
                        , 1 \
                        , _hr_\
                        , _uid_ \
                        , NULL \
                        )
