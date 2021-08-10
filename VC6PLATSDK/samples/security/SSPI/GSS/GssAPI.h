/*
 * Copyright 1993 by OpenVision Technologies, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appears in all copies and
 * that both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of OpenVision not be used
 * in advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission. OpenVision makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * OPENVISION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL OPENVISION BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _GSSAPI_H_
   #define _GSSAPI_H_

/*
 * Determine platform-dependent configuration.
 */
   #if defined(_MSDOS) || defined(_WIN32)

/* Windows 32 specific definitions */
      #define GSS_SIZEOF_INT      4
      #define GSS_SIZEOF_SHORT    2
      #define GSS_SIZEOF_LONG     4

      #ifndef KRB5_CALLCONV
         #ifdef KRB5_DLL_FILE
            #define KRB5_DECLSPEC dllexport
         #else
            #define KRB5_DECLSPEC dllimport
         #endif
         #define KRB5_DLLIMP __declspec(KRB5_DECLSPEC)
         #define KRB5_CALLCONV __stdcall
         #define KRB5_CALLCONV_C __cdecl
         #define INTERFACE   KRB5_DLLIMP KRB5_CALLCONV
         #define INTERFACE_C KRB5_DLLIMP KRB5_CALLCONV_C
      #endif /* !KRB5_CALLCONV */

      #include <windows.h>

      #ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
         #define _SIZE_T_DEFINED
      #endif /* _SIZE_T_DEFINED */

      #ifndef _UID_T_DEFINED
typedef unsigned int uid_t;
         #define _UID_T_DEFINED
      #endif
   #else /* _MSDOS_ */

      #ifndef KRB5_CALLCONV
         #define KRB5_CALLCONV
         #define KRB5_CALLCONV_C
         #define KRB5_DLLIMP
         #define INTERFACE
         #define INTERFACE_C
         #define FAR
         #define NEAR
      #endif /* !KRB5_CALLCONV */

      #define GSS_SIZEOF_INT          SIZEOF_INT
      #define GSS_SIZEOF_LONG         SIZEOF_LONG
      #define GSS_SIZEOF_SHORT        SIZEOF_SHORT
   #endif /* _MSDOS */

   #ifndef FAR
      #define FAR
   #endif
   #ifndef NEAR
      #define NEAR
   #endif

/*
 * Make sure we have a definition for PROTOTYPE.
 */
   #if !defined(PROTOTYPE)
      #define PROTOTYPE(x) x
   #endif

   #include <stddef.h>

   #include <sys/types.h>

typedef void FAR * gss_name_t;
typedef void FAR * gss_cred_id_t;
typedef void FAR * gss_ctx_id_t;

typedef unsigned long gss_uint32;
typedef long gss_int32;

typedef gss_uint32      OM_uint32;

typedef struct gss_OID_desc_struct
{
   OM_uint32 length;
   void      FAR *elements;
} gss_OID_desc, FAR *gss_OID;

typedef struct gss_OID_set_desc_struct
{
   size_t  count;
   gss_OID elements;
} gss_OID_set_desc, FAR *gss_OID_set;

typedef struct gss_buffer_desc_struct
{
   size_t length;
   void FAR *value;
} gss_buffer_desc, FAR *gss_buffer_t;

typedef struct gss_channel_bindings_struct
{
   OM_uint32 initiator_addrtype;
   gss_buffer_desc initiator_address;
   OM_uint32 acceptor_addrtype;
   gss_buffer_desc acceptor_address;
   gss_buffer_desc application_data;
} FAR *gss_channel_bindings_t;

/*
 * For now, define a QOP-type as an OM_uint32 (pending resolution of ongoing
 * discussions).
 */
typedef OM_uint32       gss_qop_t;
typedef int             gss_cred_usage_t;

/*
 * Flag bits for context-level services.
 */
   #define GSS_C_DELEG_FLAG 1
   #define GSS_C_MUTUAL_FLAG 2
   #define GSS_C_REPLAY_FLAG 4
   #define GSS_C_SEQUENCE_FLAG 8
   #define GSS_C_CONF_FLAG 16
   #define GSS_C_INTEG_FLAG 32
   #define GSS_C_ANON_FLAG 64

/*
 * Credential usage options
 */
   #define GSS_C_BOTH 0
   #define GSS_C_INITIATE 1
   #define GSS_C_ACCEPT 2

/*
 * Status code types for gss_display_status
 */
   #define GSS_C_GSS_CODE 1
   #define GSS_C_MECH_CODE 2

/*
 * The constant definitions for channel-bindings address families
 */
   #define GSS_C_AF_UNSPEC     0
   #define GSS_C_AF_LOCAL      1
   #define GSS_C_AF_INET       2
   #define GSS_C_AF_IMPLINK    3
   #define GSS_C_AF_PUP        4
   #define GSS_C_AF_CHAOS      5
   #define GSS_C_AF_NS         6
   #define GSS_C_AF_NBS        7
   #define GSS_C_AF_ECMA       8
   #define GSS_C_AF_DATAKIT    9
   #define GSS_C_AF_CCITT      10
   #define GSS_C_AF_SNA        11
   #define GSS_C_AF_DECnet     12
   #define GSS_C_AF_DLI        13
   #define GSS_C_AF_LAT        14
   #define GSS_C_AF_HYLINK     15
   #define GSS_C_AF_APPLETALK  16
   #define GSS_C_AF_BSC        17
   #define GSS_C_AF_DSS        18
   #define GSS_C_AF_OSI        19
   #define GSS_C_AF_X25        21

   #define GSS_C_AF_NULLADDR   255

/*
 * Various Null values.
 */
   #define GSS_C_NO_BUFFER ((gss_buffer_t) 0)
   #define GSS_C_NO_OID ((gss_OID) 0)
   #define GSS_C_NO_OID_SET ((gss_OID_set) 0)
   #define GSS_C_NO_CONTEXT ((gss_ctx_id_t) 0)
   #define GSS_C_NO_CREDENTIAL ((gss_cred_id_t) 0)
   #define GSS_C_NO_CHANNEL_BINDINGS ((gss_channel_bindings_t) 0)
   #define GSS_C_EMPTY_BUFFER {0, NULL}

/*
 * Some alternate names for a couple of the above values.  These are defined
 * for V1 compatibility.
 */
   #define GSS_C_NULL_OID          GSS_C_NO_OID
   #define GSS_C_NULL_OID_SET      GSS_C_NO_OID_SET

/*
 * Define the default Quality of Protection for per-message services.  Note
 * that an implementation that offers multiple levels of QOP may either reserve
 * a value (for example zero, as assumed here) to mean "default protection", or
 * alternatively may simply equate GSS_C_QOP_DEFAULT to a specific explicit
 * QOP value.  However a value of 0 should always be interpreted by a GSSAPI
 * implementation as a request for the default protection level.
 */
   #define GSS_C_QOP_DEFAULT 0

/*
 * Expiration time of 2^32-1 seconds means infinite lifetime for a
 * credential or security context
 */
   #define GSS_C_INDEFINITE ((OM_uint32) 0xfffffffful)


/* Major status codes */

   #define GSS_S_COMPLETE 0

/*
 * Some "helper" definitions to make the status code macros obvious.
 */
   #define GSS_C_CALLING_ERROR_OFFSET 24
   #define GSS_C_ROUTINE_ERROR_OFFSET 16
   #define GSS_C_SUPPLEMENTARY_OFFSET 0
   #define GSS_C_CALLING_ERROR_MASK ((OM_uint32) 0377ul)
   #define GSS_C_ROUTINE_ERROR_MASK ((OM_uint32) 0377ul)
   #define GSS_C_SUPPLEMENTARY_MASK ((OM_uint32) 0177777ul)

/*
 * The macros that test status codes for error conditions.  Note that the
 * GSS_ERROR() macro has changed slightly from the V1 GSSAPI so that it now
 * evaluates its argument only once.
 */
   #define GSS_CALLING_ERROR(x) \
  ((x) & (GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET))
   #define GSS_ROUTINE_ERROR(x) \
  ((x) & (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET))
   #define GSS_SUPPLEMENTARY_INFO(x) \
  ((x) & (GSS_C_SUPPLEMENTARY_MASK << GSS_C_SUPPLEMENTARY_OFFSET))
   #define GSS_ERROR(x) \
  ((x) & ((GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET) | \
          (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET)))

/*
 * Now the actual status code definitions
 */

/*
 * Calling errors:
 */
   #define GSS_S_CALL_INACCESSIBLE_READ \
                             (((OM_uint32) 1ul) << GSS_C_CALLING_ERROR_OFFSET)
   #define GSS_S_CALL_INACCESSIBLE_WRITE \
                             (((OM_uint32) 2ul) << GSS_C_CALLING_ERROR_OFFSET)
   #define GSS_S_CALL_BAD_STRUCTURE \
                             (((OM_uint32) 3ul) << GSS_C_CALLING_ERROR_OFFSET)

/*
 * Routine errors:
 */
   #define GSS_S_BAD_MECH (((OM_uint32) 1ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_BAD_NAME (((OM_uint32) 2ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_BAD_NAMETYPE (((OM_uint32) 3ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_BAD_BINDINGS (((OM_uint32) 4ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_BAD_STATUS (((OM_uint32) 5ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_BAD_SIG (((OM_uint32) 6ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_NO_CRED (((OM_uint32) 7ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_NO_CONTEXT (((OM_uint32) 8ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_DEFECTIVE_TOKEN (((OM_uint32) 9ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_DEFECTIVE_CREDENTIAL \
     (((OM_uint32) 10ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_CREDENTIALS_EXPIRED \
     (((OM_uint32) 11ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_CONTEXT_EXPIRED \
     (((OM_uint32) 12ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_FAILURE (((OM_uint32) 13ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_BAD_QOP (((OM_uint32) 14ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_UNAUTHORIZED (((OM_uint32) 15ul) << GSS_C_ROUTINE_ERROR_OFFSET)
   #define GSS_S_UNAVAILABLE (((OM_uint32) 16ul) << GSS_C_ROUTINE_ERROR_OFFSET)
/*
 * XXX new functions.  Check to get official error number assigments?
 */
   #define GSS_S_DUPLICATE_ELEMENT \
     (((OM_uint32) 17ul) << GSS_C_ROUTINE_ERROR_OFFSET)

/*
 * Supplementary info bits:
 */
   #define GSS_S_CONTINUE_NEEDED (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 0))
   #define GSS_S_DUPLICATE_TOKEN (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 1))
   #define GSS_S_OLD_TOKEN (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 2))
   #define GSS_S_UNSEQ_TOKEN (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 3))
/*
 * XXX not in the cbindings yet.  remove this comment when it is
 */
   #define GSS_S_GAP_TOKEN (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 4))


/*
 * Finally, function prototypes for the GSSAPI routines.
 */

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_acquire_cred
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_name_t,                 /* desired_name */
            OM_uint32,                  /* time_req */
            gss_OID_set,                /* desired_mechs */
            gss_cred_usage_t,           /* cred_usage */
            gss_cred_id_t FAR *,        /* output_cred_handle */
            gss_OID_set FAR *,          /* actual_mechs */
            OM_uint32 FAR *             /* time_rec */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_release_cred
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_cred_id_t FAR *         /* cred_handle */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_init_sec_context
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_cred_id_t,              /* claimant_cred_handle */
            gss_ctx_id_t FAR *,         /* context_handle */
            gss_name_t,                 /* target_name */
            gss_OID,                    /* mech_type (used to be const) */
            OM_uint32,                  /* req_flags */
            OM_uint32,                  /* time_req */
            gss_channel_bindings_t,     /* input_chan_bindings */
            gss_buffer_t,               /* input_token */
            gss_OID FAR *,              /* actual_mech_type */
            gss_buffer_t,               /* output_token */
            OM_uint32 FAR *,            /* ret_flags */
            OM_uint32 FAR *             /* time_rec */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_accept_sec_context
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t FAR *,         /* context_handle */
            gss_cred_id_t,              /* acceptor_cred_handle */
            gss_buffer_t,               /* input_token_buffer */
            gss_channel_bindings_t,     /* input_chan_bindings */
            gss_name_t FAR *,           /* src_name */
            gss_OID FAR *,              /* mech_type */
            gss_buffer_t,               /* output_token */
            OM_uint32 FAR *,            /* ret_flags */
            OM_uint32 FAR *,            /* time_rec */
            gss_cred_id_t FAR *         /* delegated_cred_handle */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_process_context_token
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t,               /* context_handle */
            gss_buffer_t                /* token_buffer */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_delete_sec_context
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t FAR *,         /* context_handle */
            gss_buffer_t                /* output_token */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_context_time
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t,               /* context_handle */
            OM_uint32 FAR *             /* time_rec */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_get_mic
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t,               /* context_handle */
            gss_qop_t,                  /* qop_req */
            gss_buffer_t,               /* message_buffer */
            gss_buffer_t                /* message_token */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_verify_mic
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t,               /* context_handle */
            gss_buffer_t,               /* message_buffer */
            gss_buffer_t,               /* message_token */
            gss_qop_t *                 /* qop_state */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_wrap
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t,               /* context_handle */
            int,                        /* conf_req_flag */
            gss_qop_t,                  /* qop_req */
            gss_buffer_t,               /* input_message_buffer */
            int FAR *,                  /* conf_state */
            gss_buffer_t                /* output_message_buffer */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_unwrap
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t,               /* context_handle */
            gss_buffer_t,               /* input_message_buffer */
            gss_buffer_t,               /* output_message_buffer */
            int FAR *,                  /* conf_state */
            gss_qop_t FAR *             /* qop_state */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_display_status
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            OM_uint32,                  /* status_value */
            int,                        /* status_type */
            gss_OID,                    /* mech_type (used to be const) */
            OM_uint32 FAR *,            /* message_context */
            gss_buffer_t                /* status_string */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_indicate_mechs
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_OID_set FAR *           /* mech_set */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_compare_name
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_name_t,                 /* name1 */
            gss_name_t,                 /* name2 */
            int FAR *                   /* name_equal */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_display_name
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_name_t,                 /* input_name */
            gss_buffer_t,               /* output_name_buffer */
            gss_OID FAR *               /* output_name_type */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_import_name
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_buffer_t,               /* input_name_buffer */
            gss_OID,                    /* input_name_type(used to be const) */
            gss_name_t FAR *            /* output_name */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_release_name
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_name_t FAR *            /* input_name */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_release_buffer
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_buffer_t                /* buffer */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_release_oid_set
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_OID_set FAR *           /* set */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_inquire_cred
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_cred_id_t,              /* cred_handle */
            gss_name_t FAR *,           /* name */
            OM_uint32 FAR *,            /* lifetime */
            gss_cred_usage_t FAR *,     /* cred_usage */
            gss_OID_set FAR *           /* mechanisms */
           ));

/* Last argument new for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_inquire_context
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t,               /* context_handle */
            gss_name_t FAR *,           /* src_name */
            gss_name_t FAR *,           /* targ_name */
            OM_uint32 FAR *,            /* lifetime_rec */
            gss_OID FAR *,              /* mech_type */
            OM_uint32 FAR *,            /* ctx_flags */
            int FAR *,                  /* locally_initiated */
            int FAR *                   /* open */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_wrap_size_limit
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t,               /* context_handle */
            int,                        /* conf_req_flag */
            gss_qop_t,                  /* qop_req */
            OM_uint32,                  /* req_output_size */
            OM_uint32 *                 /* max_input_size */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_import_name_object
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            void FAR *,                 /* input_name */
            gss_OID,                    /* input_name_type */
            gss_name_t FAR *            /* output_name */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_export_name_object
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_name_t,                 /* input_name */
            gss_OID,                    /* desired_name_type */
            void FAR * FAR *            /* output_name */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_add_cred
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_cred_id_t,              /* input_cred_handle */
            gss_name_t,                 /* desired_name */
            gss_OID,                    /* desired_mech */
            gss_cred_usage_t,           /* cred_usage */
            OM_uint32,                  /* initiator_time_req */
            OM_uint32,                  /* acceptor_time_req */
            gss_cred_id_t FAR *,        /* output_cred_handle */
            gss_OID_set FAR *,          /* actual_mechs */
            OM_uint32 FAR *,            /* initiator_time_rec */
            OM_uint32 FAR *             /* acceptor_time_rec */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_inquire_cred_by_mech
PROTOTYPE( (OM_uint32  FAR *,           /* minor_status */
            gss_cred_id_t,              /* cred_handle */
            gss_OID,                    /* mech_type */
            gss_name_t FAR *,           /* name */
            OM_uint32 FAR *,            /* initiator_lifetime */
            OM_uint32 FAR *,            /* acceptor_lifetime */
            gss_cred_usage_t FAR *      /* cred_usage */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_export_sec_context
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_ctx_id_t FAR *,         /* context_handle */
            gss_buffer_t                /* interprocess_token */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_import_sec_context
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_buffer_t,               /* interprocess_token */
            gss_ctx_id_t FAR *          /* context_handle */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_release_oid
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_OID FAR *               /* oid */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_create_empty_oid_set
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_OID_set FAR *           /* oid_set */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_add_oid_set_member
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_OID,                    /* member_oid */
            gss_OID_set FAR *           /* oid_set */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_test_oid_set_member
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_OID,                    /* member */
            gss_OID_set,                /* set */
            int FAR *                   /* present */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_str_to_oid
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_buffer_t,               /* oid_str */
            gss_OID FAR *               /* oid */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_oid_to_str
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_OID,                    /* oid */
            gss_buffer_t                /* oid_str */
           ));

/* New for V2 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_inquire_names_for_mech
PROTOTYPE( (OM_uint32 FAR *,            /* minor_status */
            gss_OID,                    /* mechanism */
            gss_OID_set FAR *           /* name_types */
           ));

/*
 * The following routines are obsolete variants of gss_get_mic, gss_wrap,
 * gss_verify_mic and gss_unwrap.  They should be provided by GSSAPI V2
 * implementations for backwards compatibility with V1 applications.  Distinct
 * entrypoints (as opposed to #defines) should be provided, to allow GSSAPI
 * V1 applications to link against GSSAPI V2 implementations.
 */
KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_sign
PROTOTYPE( (OM_uint32 FAR *,    /* minor_status */
            gss_ctx_id_t,       /* context_handle */
            int,                /* qop_req */
            gss_buffer_t,       /* message_buffer */
            gss_buffer_t        /* message_token */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_verify
PROTOTYPE( (OM_uint32 FAR *,    /* minor_status */
            gss_ctx_id_t,       /* context_handle */
            gss_buffer_t,       /* message_buffer */
            gss_buffer_t,       /* token_buffer */
            int FAR *           /* qop_state */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_seal
PROTOTYPE( (OM_uint32 FAR *,    /* minor_status */
            gss_ctx_id_t,       /* context_handle */
            int,                /* conf_req_flag */
            int,                /* qop_req */
            gss_buffer_t,       /* input_message_buffer */
            int FAR *,          /* conf_state */
            gss_buffer_t        /* output_message_buffer */
           ));

KRB5_DLLIMP OM_uint32 KRB5_CALLCONV gss_unseal
PROTOTYPE( (OM_uint32 FAR *,    /* minor_status */
            gss_ctx_id_t,       /* context_handle */
            gss_buffer_t,       /* input_message_buffer */
            gss_buffer_t,       /* output_message_buffer */
            int FAR *,          /* conf_state */
            int FAR *           /* qop_state */
           ));

/* XXXX these are not part of the GSSAPI C bindings!  (but should be) */

   #define GSS_CALLING_ERROR_FIELD(x) \
   (((x) >> GSS_C_CALLING_ERROR_OFFSET) & GSS_C_CALLING_ERROR_MASK)
   #define GSS_ROUTINE_ERROR_FIELD(x) \
   (((x) >> GSS_C_ROUTINE_ERROR_OFFSET) & GSS_C_ROUTINE_ERROR_MASK)
   #define GSS_SUPPLEMENTARY_INFO_FIELD(x) \
   (((x) >> GSS_C_SUPPLEMENTARY_OFFSET) & GSS_C_SUPPLEMENTARY_MASK)

/* XXXX This is a necessary evil until the spec is fixed */
   #define GSS_S_CRED_UNAVAIL GSS_S_FAILURE

#endif /* _GSSAPI_H_ */
