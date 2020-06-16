/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/
#ifndef __CUMODULEENUMH__
#define __CUMODULEENUMH__

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************
***********************************************************************************
******************* Common           Enum          Type ***************************
***********************************************************************************
***********************************************************************************/
typedef enum
{
	NEXT_PAGING_AREA_SCOPE_SAME 	= 0,
	NEXT_PAGING_AREA_SCOPE_CHANGED	= 1
}NextPagingAreaScope_e;

typedef enum
{
	PAGING_ORIGIN_NON_3GPP = 0
}PagingOrigin_e;

typedef enum
{
	RRC_STATE_INACTIVE 	= 0,
	RRC_STATE_CONNECTED	= 1
}RrcState_e;

typedef enum
{
	DATA_FORWARDING_ACCEPTED = 0
}DataForwardAccepted_e;

typedef enum
{
	EVENT_TYPE_direct								= 0,
	EVENT_TYPE_change_of_serve_cell					= 1,
	EVENT_TYPE_ue_presence_in_area_of_interest		= 2,
	EVENT_TYPE_stop_change_of_serve_cell 			= 3,
	EVENT_TYPE_stop_ue_presence_in_area_of_interest	= 4,
	EVENT_TYPE_cancel_location_reporting_for_the_ue	= 5
}EventType_e;

typedef enum
{
	REPORT_AREA_CELL = 0
}ReportArea_e;

typedef enum
{
	HANDOVERTYPE_INTRA_5GS 	= 0,
	HANDOVERTYPE_5GS_TO_EPS	= 1,
	HANDOVERTYPE_EPS_TO_5GS	= 2
}HandoverType_e;

typedef enum
{
	DL_NGU_TNL_INFO_REUSED_TRUE = 0
}DlNguTnlInfoReused_e;

typedef enum
{
	NEW_SECURITY_CONTEXT_IND_TRUE = 0
}NewSecurityCtxInd_e;

typedef enum 
{
	TIME_WAIT_1S	= 0,
	TIME_WAIT_2S	= 1,
	TIME_WAIT_5S	= 2,
	TIME_WAIT_10S   = 3,
	TIME_WAIT_20S   = 4,
	TIME_WAIT_60S   = 5
} TimeToWait_e;

typedef enum
{
	INITIATING_MESSAGE		= 0,
	SUCCESSFUL_OUTCOME		= 1,
	UNSUCCESSFUL_OUTCOME	= 2
} TriggerMsg_e;

typedef enum
{
	CRITICALITY_REJECT = 0,
	CRITICALITY_IGNORE = 1,
	CRITICALITY_NOTIFY = 2
} Criticality_e;

typedef enum 
{
	ERROR_NOT_UNDERSTOOD	= 0,
	ERROR_MISSING			= 1
} ErrorType_e;

typedef enum 
{
	CN_SUPPORT_EPC 	= 0,
	CN_SUPPORT_5GC 	= 1,
	CN_SUPPORT_BOTH	= 2
}CNSupport_e;

typedef enum pduSessType
{
	Pdu_Session_Type_ipv4			= 0,
	Pdu_Session_Type_ipv6			= 1,
	Pdu_Session_Type_ipv4v6			= 2,
	Pdu_Session_Type_ethernet		= 3,
	Pdu_Session_Type_unstructured	= 4
} PduSessType_e;

typedef enum iPIndication 
{
	IP_REQUIRED		 = 0,
	IP_PREFERRED	 = 1,
	IP_NOT_NEEDED	 = 2
} IPIndication_e;

typedef enum cPIndication 
{
	CP_REQUIRED		 = 0,
	CP_PREFERRED	 = 1,
	CP_NOT_NEEDED	 = 2
} CPIndication_e;

typedef enum maxIpDataRate 
{
	BITRATE_64K		= 0,
	MAX_UE_RATE		= 1
} MaxIpDataRate_e;

typedef enum iPResult 
{
	IP_RESULT_PERFORMED		= 0,
	IP_RESULT_NOT_PERFORMED = 1
} IPResult_e;

typedef enum cPResult 
{
	CP_RESULT_PERFORMED		= 0,
	CP_RESULT_NOT_PERFORMED = 1
} CPResult_e;

typedef enum 
{
	Dynamic5QIDelayCritical_delay_critical	= 0,
	Dynamic5QIDelayCritical_non_delay_critical	= 1
} Dynamic5QIDelayCritical_e;

typedef enum 
{
	PreEmptionCapability_shall_not_trigger_pre_emption	= 0,
	PreEmptionCapability_may_trigger_pre_emption	= 1
} PreEmptionCapability_e;

typedef enum 
{
	PreEmptionVulnerability_not_pre_emptable	= 0,
	PreEmptionVulnerability_pre_emptable	= 1
} PreEmptionVulnerability_e;


typedef enum
{
	QOS_CHARACTER_PR_NOTHING,	
	QOS_CHARACTER_PR_NON_DINAMIC_5QI,
	QOS_CHARACTER_PR_DYNAMIC_5QI,
	QOS_CHARACTER_PR_CHOICE_EXTENSION
} QosCharacterPR_e;

typedef enum
{
	ADDITIONAL_QOS_FLOW_INFORMATION_MORE_LIKELY
} AddQosFlowInfo_e;

typedef enum
{
	REFLECTIVE_QOS_ATTRIBUTE_SUBJECT_TO
} ReflectiveQosAttribute_e;

typedef enum
{
	QOS_FLOW_MAP_IND_UL,
	QOS_FLOW_MAP_IND_DL
} QosFlowMapInd_e;

/**********************************************************************************
***********************************************************************************
********************* NG			 Enum		   Type ***************************
***********************************************************************************
***********************************************************************************/

typedef enum ngapCause_s
{		
	NG_START,
	Ng_RNL_UNSPECIFIED,
	Ng_RNL_TXnRELOCOverallExpiry,
	Ng_RNL_Successful_handover,
	NG_RNL_RELEASE_DUE_TO_GENERATED_REASON,
	NG_RNL_RELEASE_DUE_TO_5GC_GENERATE_REASON,
	NG_RNL_HANDOVER_CANCELLED,
	NG_RNL_PARTIAL_HANDOVER,
	NG_RNL_HANDOVER_FAILURE_IN_TARGET_5GC_NGRAN_NODE_OR_TARGET_SYSTEM,
	NG_RNL_HANDOVER_FAILURE_5GC_NGRAN_OR_SYSTEM,
	NG_RNL_HANDOVER_TARGET_NOT_ALLOWED,
	NG_RNL_TNGRELOCOVERALL_EXPIRY,
	NG_RNL_TNGRELOCPREP_EXPIRY,
	NG_RNL_CELL_NOT_AVAILABLE,
	NG_RNL_UNKNOWN_TARGET_ID,
	NG_RNL_NO_RADIO_RESOURCES_AVAILABLE_IN_TARGET_CELL,
	NG_RNL_UNKNOWN_LOCAL_UE_NGAP_ID,
	NG_RNL_INCONSISTENT_REMOTE_UE_NGAP_ID,
	NG_RNL_HANDOVER_DESIRABLE_FOR_RADIO_REASONS,	
	NG_RNL_TIME_CRITICAL_HANDOVER,
	NG_RNL_RESOURCE_OPTIMISATION_HANDOVER,
	NG_RNL_REDUCE_LOAD_IN_SERVING_CELL,
	NG_RNL_USER_INACTIVITY,
	NG_RNL_RADIO_CONNECTION_WITH_UE_LOST,
	NG_RNL_RADIO_RESOURCES_NOT_AVAILABLE,
	NG_RNL_INVALID_QOS_COMBINATION,
	NG_RNL_FAILURE_IN_THE_RADIO_INTERFACE_PROCEDURE,
	NG_RNL_INTERACTION_WITH_OTHER_PROCEDURE,
	NG_RNL_UNKNOWN_PDU_SESSION_ID,
	NG_RNL_UNKNOWN_QOS_FLOW_ID,
	NG_RNL_MULTIPLE_PDU_SESSION_ID_INSTANCES,
	NG_RNL_MULTIPLE_QOS_FLOW_ID_INSTANCES,
	NG_RNL_ENCRYPTION_AND_OR_INTEGRITY_PROTECTION_ALGORITHMS_NOT_SUPPORTED,
	NG_RNL_NG_INTRA_SYSTEM_HANDOVER_TRIGGERED,
	NG_RNL_NG_INTER_SYSTEM_HANDOVER_TRIGGERED,
	NG_RNL_XN_HANDOVER_TRIGGERED,
	NG_RNL_NOT_SUPPORTED_5QI_VALUE,
	NG_RNL_UE_CONTEXT_TRANSFER,
	NG_RNL_IMS_VOICE_EPS_FALLBACK_OR_RAT_FALLBACK_TRIGGERED,
	NG_RNL_UP_INTEGRITY_PROTECTION_NOT_POSSIBLE,
	NG_RNL_UP_CONFIDENTIALITY_PROTECTION_NOT_POSSIBLE,
	NG_RNL_SLICE_NOT_SUPPORTED,
	NG_RNL_UE_IN_RRC_INACTIVE_STATE_NOT_REACHABLE,
	NG_RNL_REDIRECTION,
	NG_RNL_RESOURCES_NOT_AVAILABLE_FOR_THE_SLICE,
	NG_RNL_UE_MAXIMUM_INTEGRITY_PROTECTED_DATA_RATE_REASON,
	NG_RNL_RELEASE_DUE_TO_CN_DETECTED_MOBILITY,
	NG_RNL_N26_INTERFACE_NOT_AVAILABLE,
	NG_RNL_RELEASE_DUE_TO_PRE_EMPTION,
	NG_RNL_END,	
	NG_TL_TRANSPORT_RESOURCE_UNAVAILABLE,
	NG_TL_UNSPECIFIED,
	NG_TL_END,
	NG_NAS_NORMAL_RELEASE,
	NG_NAS_AUTHENTICATION_FAILURE,
	NG_NAS_DEREGISTER,
	NG_NAS_UNSPECIFIED,
	NG_NAS_END,
	NG_PC_TRANSFER_SYNTAX_ERROR,
	NG_PC_ABSTRACT_SYNTAX_ERROR_REJECT,
	NG_PC_ABSTRACT_SYNTAX_ERROR_IGNORE_AND_NOTIFY,
	NG_PC_MESSAGE_NOT_COMPATIBLE_WITH_RECEIVER_STATE,
	NG_PC_SEMANTIC_ERROR,
	NG_PC_ABSTRACT_SYNTAX_ERROR,
	NG_PC_UNSPECIFIED,
	NG_PC_END,
	NG_MISC_CONTROL_PROCESSING_OVERLOAD, 
	NG_MISC_NOT_ENOUGH_USER_PLANE_PROCESSING_RESOURCES,
	NG_MISC_HARDWARE_FAILURE,
	NG_MISC_OM_INTERVENTION,
	NG_MISC_UNKNOWN_PLMN,
	NG_MISC_UNSPECIFIED,
	NG_MISC_END,
	NG_END
}NgapCause_e; 

typedef enum ngapProcCode 
{
	Ng_AMFConfigurationUpdate					= 0,
	Ng_AMFStatusIndication						= 1,
	Ng_CellTrafficTrace							= 2,
	Ng_DeactivateTrace							= 3,
	Ng_DownlinkNASTransport						= 4,
	Ng_DownlinkNonUEAssociatedNRPPaTransport	= 5,
	Ng_DownlinkRANConfigurationTransfer			= 6,
	Ng_DownlinkRANStatusTransfer				= 7,
	Ng_DownlinkUEAssociatedNRPPaTransport		= 8,
	Ng_NGErrorIndication						= 9,
	Ng_HandoverCancel							= 10,
	Ng_HandoverNotification						= 11,
	Ng_HandoverPreparation						= 12,
	Ng_HandoverResourceAllocation				= 13,
	Ng_InitialContextSetup						= 14,
	Ng_InitialUEMessage							= 15,
	Ng_LocationReportingControl					= 16,
	Ng_LocationReportingFailureIndication		= 17,
	Ng_LocationReport							= 18,
	Ng_NASNonDeliveryIndication					= 19,
	Ng_NGReset									= 20,
	Ng_NGSetup									= 21,
	Ng_OverloadStart							= 22,
	Ng_OverloadStop								= 23,
	Ng_NGPaging									= 24,
	Ng_PathSwitchRequest						= 25,
	Ng_PDUSessionResourceModify					= 26,
	Ng_PDUSessionResourceModifyIndication		= 27,
	Ng_PDUSessionResourceRelease				= 28,
	Ng_PDUSessionResourceSetup					= 29,
	Ng_PDUSessionResourceNotify					= 30,
	Ng_NGPrivateMessage							= 31,
	Ng_NGPWSCancel								= 32,
	Ng_NGPWSFailureIndication					= 33,
	Ng_NGPWSRestartIndication					= 34,
	Ng_RANConfigurationUpdate					= 35,
	Ng_RerouteNASRequest						= 36,
	Ng_RRCInactiveTransitionReport				= 37,
	Ng_TraceFailureIndication					= 38,
	Ng_TraceStart								= 39,
	Ng_NGUEContextModification					= 40,
	Ng_NGUEContextRelease						= 41,
	Ng_NGUEContextReleaseRequest				= 42,
	Ng_UERadioCapabilityCheck					= 43,
	Ng_UERadioCapabilityInfoIndication			= 44,
	Ng_UETNLABindingRelease						= 45,
	Ng_UplinkNASTransport						= 46,
	Ng_UplinkNonUEAssociatedNRPPaTransport		= 47,
	Ng_UplinkRANConfigurationTransfer			= 48,
	Ng_UplinkRANStatusTransfer					= 49,
	Ng_UplinkUEAssociatedNRPPaTransport			= 50,
	Ng_WriteReplaceWarning						= 51,
	Ng_SecondaryRATDataUsageReport				= 52
} NgapProcCode_e;

typedef enum ngapProtocolIeId 
{
	Ngap_AllowedNSSAI								= 0,
	Ngap_AMFName									= 1,
	Ngap_AMFOverloadResponse						= 2,
	Ngap_AMFSetID									= 3,
	Ngap_AMF_TNLAssociationFailedToSetupList		= 4,
	Ngap_AMF_TNLAssociationSetupList				= 5,
	Ngap_AMF_TNLAssociationToAddList				= 6,
	Ngap_AMF_TNLAssociationToRemoveList				= 7,
	Ngap_AMF_TNLAssociationToUpdateList				= 8,
	Ngap_AMFTrafficLoadReductionIndication			= 9,
	Ngap_AMF_UE_NGAP_ID								= 10,
	Ngap_AssistanceDataForPaging					= 11,
	Ngap_BroadcastCancelledAreaList					= 12,
	Ngap_BroadcastCompletedAreaList					= 13,
	Ngap_CancelAllWarningMessages					= 14,
	Ngap_NGCause									= 15,
	Ngap_CellIDListForRestart						= 16,
	Ngap_ConcurrentWarningMessageInd				= 17,
	Ngap_CoreNetworkAssistanceInformation			= 18,
	Ngap_NGCriticalityDiagnostics					= 19,
	Ngap_DataCodingScheme							= 20,
	Ngap_DefaultPagingDRX							= 21,
	Ngap_DirectForwardingPathAvailability			= 22,
	Ngap_EmergencyAreaIDListForRestart				= 23,
	Ngap_EmergencyFallbackIndicator					= 24,
	Ngap_EUTRA_CGI									= 25,
	Ngap_FiveG_S_TMSI								= 26,
	Ngap_GlobalRANNodeID							= 27,
	Ngap_GUAMI										= 28,
	Ngap_HandoverType								= 29,
	Ngap_IMSVoiceSupportIndicator					= 30,
	Ngap_IndexToRFSP								= 31,
	Ngap_InfoOnRecommendedCellsAndRANNodesForPaging	= 32,
	Ngap_LocationReportingRequestType				= 33,
	Ngap_NGMaskedIMEISV								= 34,
	Ngap_MessageIdentifier							= 35,
	Ngap_MobilityRestrictionList					= 36,
	Ngap_NASC										= 37,
	Ngap_NAS_PDU									= 38,
	Ngap_NASSecurityParametersFromNGRAN				= 39,
	Ngap_NewAMF_UE_NGAP_ID							= 40,
	Ngap_NewSecurityContextInd						= 41,
	Ngap_NGAP_Message								= 42,
	Ngap_NGRAN_CGI									= 43,
	Ngap_NGRANTraceID								= 44,
	Ngap_NGNR_CGI									= 45,
	Ngap_NRPPa_PDU									= 46,
	Ngap_NumberOfBroadcastsRequested				= 47,
	Ngap_OldAMF										= 48,
	Ngap_OverloadStartNSSAIList						= 49,
	Ngap_NGPagingDRX								= 50,
	Ngap_PagingOrigin								= 51,
	Ngap_NGPagingPriority							= 52,
	Ngap_PDUSessionResourceAdmittedList				= 53,
	Ngap_PDUSessionResourceFailedToModifyListModRes	= 54,
	Ngap_PDUSessionResourceFailedToSetupListCxtRes	= 55,
	Ngap_PDUSessionResourceFailedToSetupListHOAck	= 56,
	Ngap_PDUSessionResourceFailedToSetupListPSReq	= 57,
	Ngap_PDUSessionResourceFailedToSetupListSURes	= 58,
	Ngap_PDUSessionResourceHandoverList				= 59,
	Ngap_PDUSessionResourceListCxtRelCpl			= 60,
	Ngap_PDUSessionResourceListHORqd				= 61,
	Ngap_PDUSessionResourceModifyListModCfm			= 62,
	Ngap_PDUSessionResourceModifyListModInd			= 63,
	Ngap_PDUSessionResourceModifyListModReq			= 64,
	Ngap_PDUSessionResourceModifyListModRes			= 65,
	Ngap_PDUSessionResourceNotifyList				= 66,
	Ngap_PDUSessionResourceReleasedListNot			= 67,
	Ngap_PDUSessionResourceReleasedListPSAck		= 68,
	Ngap_PDUSessionResourceReleasedListPSFail		= 69,
	Ngap_PDUSessionResourceReleasedListRelRes		= 70,
	Ngap_PDUSessionResourceSetupListCxtReq			= 71,
	Ngap_PDUSessionResourceSetupListCxtRes			= 72,
	Ngap_PDUSessionResourceSetupListHOReq			= 73,
	Ngap_PDUSessionResourceSetupListSUReq			= 74,
	Ngap_PDUSessionResourceSetupListSURes			= 75,
	Ngap_PDUSessionResourceToBeSwitchedDLList		= 76,
	Ngap_PDUSessionResourceSwitchedList				= 77,
	Ngap_PDUSessionResourceToReleaseListHOCmd		= 78,
	Ngap_PDUSessionResourceToReleaseListRelCmd		= 79,
	Ngap_PLMNSupportList							= 80,
	Ngap_PWSFailedCellIDList						= 81,
	Ngap_RANNodeName								= 82,
	Ngap_RANPagingPriority							= 83,
	Ngap_RANStatusTransfer_TransparentContainer		= 84,
	Ngap_RAN_UE_NGAP_ID								= 85,
	Ngap_RelativeAMFCapacity						= 86,
	Ngap_NGRepetitionPeriod							= 87,
	Ngap_NGResetType								= 88,
	Ngap_RoutingID									= 89,
	Ngap_RRCEstablishmentCause						= 90,
	Ngap_RRCInactiveTransitionReportRequest			= 91,
	Ngap_RRCState									= 92,
	Ngap_SecurityContext							= 93,
	Ngap_SecurityKey								= 94,
	Ngap_SerialNumber								= 95,
	Ngap_ServedGUAMIList							= 96,
	Ngap_NGSliceSupportList							= 97,
	Ngap_SONConfigurationTransferDL					= 98,
	Ngap_SONConfigurationTransferUL					= 99,
	Ngap_SourceAMF_UE_NGAP_ID						= 100,
	Ngap_SourceToTarget_TransparentContainer		= 101,
	Ngap_SupportedTAList							= 102,
	Ngap_TAIListForPaging							= 103,
	Ngap_TAIListForRestart							= 104,
	Ngap_TargetID									= 105,
	Ngap_TargetToSource_TransparentContainer		= 106,
	Ngap_NGTimeToWait								= 107,
	Ngap_TraceActivation							= 108,
	Ngap_TraceCollectionEntityIPAddress				= 109,
	Ngap_UEAggregateMaximumBitRate					= 110,
	Ngap_UE_associatedLogicalNG_connectionList		= 111,
	Ngap_UEContextRequest							= 112,
	Ngap_UE_NGAP_IDs								= 114,
	Ngap_UEPagingIdentity							= 115,
	Ngap_UEPresenceInAreaOfInterestList				= 116,
	Ngap_UERadioCapability							= 117,
	Ngap_UERadioCapabilityForPaging					= 118,
	Ngap_UESecurityCapabilities						= 119,
	Ngap_UnavailableGUAMIList						= 120,
	Ngap_UserLocationInformation					= 121,
	Ngap_WarningAreaList							= 122,
	Ngap_WarningMessageContents						= 123,
	Ngap_WarningSecurityInfo						= 124,
	Ngap_WarningType								= 125,
	Ngap_AdditionalUL_NGU_UP_TNLInformation			= 126,
	Ngap_DataForwardingNotPossible					= 127,
	Ngap_DL_NGU_UP_TNLInformation					= 128,
	Ngap_NGNetworkInstance							= 129,
	Ngap_PDUSessionAggregateMaximumBitRate			= 130,
	Ngap_PDUSessionResourceFailedToModifyListModCfm	= 131,
	Ngap_PDUSessionResourceFailedToSetupListCxtFail	= 132,
	Ngap_PDUSessionResourceListCxtRelReq			= 133,
	Ngap_PDUSessionType								= 134,
	Ngap_QosFlowAddOrModifyRequestList				= 135,
	Ngap_QosFlowSetupRequestList					= 136,
	Ngap_QosFlowToReleaseList						= 137,
	Ngap_NGSecurityIndication						= 138,
	Ngap_UL_NGU_UP_TNLInformation					= 139,
	Ngap_UL_NGU_UP_TNLModifyList					= 140,
	Ngap_WarningAreaCoordinates						= 141,
	Ngap_PDUSessionResourceSecondaryRATUsageList	= 142,
	Ngap_HandoverFlag								= 143,
	Ngap_SecondaryRATUsageInformation				= 144,
	Ngap_PDUSessionResourceReleaseResponseTransfer	= 145,
	Ngap_RedirectionVoiceFallback					= 146,
	Ngap_UERetentionInformation						= 147,
	Ngap_NGS_NSSAI									= 148,
	Ngap_PSCellInformation							= 149,
	Ngap_LastEUTRAN_PLMNIdentity					= 150,
	Ngap_MaximumIntegrityProtectedDataRate_DL		= 151,
	Ngap_AdditionalDLForwardingUPTNLInformation		= 152,
	Ngap_AdditionalDLUPTNLInformationForHOList		= 153,
	Ngap_AdditionalNGU_UP_TNLInformation			= 154,
	Ngap_AdditionalDLQosFlowPerTNLInformation		= 155,
	Ngap_NGSecurityResult							= 156,
	Ngap_ENDC_SONConfigurationTransferDL			= 157,
	Ngap_ENDC_SONConfigurationTransferUL			= 158
} NgapProtocolIeId_e;

typedef enum
{
	GUAMITYPE_NATIVE,
	GUAMITYPE_MAPPPED
}guamiType_e;

typedef enum
{
	IMSVoiceSupportInd_supported,
	IMSVoiceSupportInd_not_supported
}IMSVoiceSupportInd_e;

typedef enum
{
	rrcEstablishmentCause_emergency 			= 0,
	rrcEstablishmentCause_highPriorityAccess	= 1,
	rrcEstablishmentCause_mt_Access 			= 2,
	rrcEstablishmentCause_mo_Signalling 		= 3,
	rrcEstablishmentCause_mo_Data				= 4,
	rrcEstablishmentCause_mo_VoiceCall			= 5,
	rrcEstablishmentCause_mo_VideoCall			= 6,
	rrcEstablishmentCause_mo_SMS				= 7,
	rrcEstablishmentCause_mps_PriorityAccess	= 8,
	rrcEstablishmentCause_mcs_PriorityAccess	= 9,
	rrcEstablishmentCause_notAvailable			= 10
} RrcEstablishmentCause_e;

typedef enum
{
	CONTEXT_REQUESTED	= 0
} ueContextRequest_e;

typedef enum 
{
	amfPging_None,
	amfPging_gNBId,
	amfPging_Tai,
	amfPging_Extension
} AmfPgType_e;

typedef enum
{
	ONLY_AMF_NGAPID,
	BOTH_AMF_RAN_NGAPID
}NgapIdType_e;

typedef enum 
{
	Paging_DRX_v32	= 0,
	Paging_DRX_v64	= 1,
	Paging_DRX_v128	= 2,
	Paging_DRX_v256	= 3
} PagingDRX_e;

typedef enum
{
	PAGING_PRIORITY_LEVEL1 = 0,
	PAGING_PRIORITY_LEVEL2 = 1,
	PAGING_PRIORITY_LEVEL3 = 2,
	PAGING_PRIORITY_LEVEL4 = 3,
	PAGING_PRIORITY_LEVEL5 = 4,
	PAGING_PRIORITY_LEVEL6 = 5,
	PAGING_PRIORITY_LEVEL7 = 6,
	PAGING_PRIORITY_LEVEL8 = 7,
}PagingPriority_e;

typedef enum 
{
	UE_RETEN_INFO_UES_RETAINED	= 0
} UERetentionInformation_e;

typedef enum 
{
	EMERGENCY_FALLBACK_REQUESTED = 0
} EmergencyFallbackRequestIndicator_e;

typedef enum 
{
	EMERGENCY_SERVICE_TARGET_5GC	= 0,
	EMERGENCY_SERVICE_TARGET_epc
} EmergencyServiceTargetCN_e;

typedef enum 
{
	BEHAVIOUR_INFO_SUBSCRIPTION_INFORMATION	= 0,
	BEHAVIOUR_INFO_STATISTICS				= 1
} SourceOfUEActivityBehaviourInformation_e;

typedef enum 
{
	NotificationControl_requested	= 0
} NotificationControl_e;

typedef enum
{
	AVAILABLE = 0
}DirectForwardPathAvailability_e;

/**********************************************************************************
***********************************************************************************
********************* E1			 Enum		   Type ***************************
***********************************************************************************
***********************************************************************************/

typedef enum e1apCausePr 
{
	E1apCause_PR_NOTHING,
	E1apCause_PR_radioNetwork,
	E1apCause_PR_transport,
	E1apCause_PR_protocol,
	E1apCause_PR_misc,
	E1apCause_PR_choice_extension
} E1apCausePr_e;
typedef enum e1apResetPr
{
	E1Reset_PR_NOTHING,
	E1Reset_PR_e1_Interface,
	E1Reset_PR_partOfE1_Interface,
	E1Reset_PR_choice_extension
} E1apResetPr_e;

typedef enum e1apCauseRadioNetwork 
{
	E1apCauseRadioNetwork_unspecified = 0,
	E1apCauseRadioNetwork_unknown_or_already_allocated_gnb_cu_cp_ue_e1ap_id	= 1,
	E1apCauseRadioNetwork_unknown_or_already_allocated_gnb_cu_up_ue_e1ap_id	= 2,
	E1apCauseRadioNetwork_unknown_or_inconsistent_pair_of_ue_e1ap_id = 3,
	E1apCauseRadioNetwork_interaction_with_other_procedure = 4,
	E1apCauseRadioNetwork_pPDCP_Count_wrap_around = 5,
	E1apCauseRadioNetwork_not_supported_E1QCI_value	= 6,
	E1apCauseRadioNetwork_not_supported_5QI_value = 7,
	E1apCauseRadioNetwork_encryption_algorithms_not_supported = 8,
	E1apCauseRadioNetwork_integrity_protection_algorithms_not_supported	= 9,
	E1apCauseRadioNetwork_uP_integrity_protection_not_possible = 10,
	E1apCauseRadioNetwork_uP_confidentiality_protection_not_possible = 11,
	E1apCauseRadioNetwork_multiple_PDU_Session_ID_Instances	= 12,
	E1apCauseRadioNetwork_unknown_PDU_Session_ID = 13,
	E1apCauseRadioNetwork_multiple_QoS_Flow_ID_Instances = 14,
	E1apCauseRadioNetwork_unknown_QoS_Flow_ID = 15,
	E1apCauseRadioNetwork_multiple_E1DRB_ID_Instances = 16,
	E1apCauseRadioNetwork_unknown_E1DRB_ID = 17,
	E1apCauseRadioNetwork_invalid_QoS_combination = 18,
	E1apCauseRadioNetwork_procedure_cancelled = 19,
	E1apCauseRadioNetwork_normal_release = 20,
	E1apCauseRadioNetwork_no_radio_resources_available = 21,
	E1apCauseRadioNetwork_action_desirable_for_radio_reasons = 22,
	E1apCauseRadioNetwork_resources_not_available_for_the_slice	= 23,
	E1apCauseRadioNetwork_pDCP_configuration_not_supported	= 24,
	E1apCauseRadioNetwork_ue_dl_max_IP_data_rate_reason	= 25,
	E1apCauseRadioNetwork_uP_integrity_protection_failure = 26,
	E1apCauseRadioNetwork_release_due_to_pre_emption = 27
} E1apCauseRadioNetwork_e;

typedef enum e1apCauseTransport 
{
	E1apCauseTransport_unspecified	= 0,
	E1apCauseTransport_transport_resource_unavailable	= 1
} E1apCauseTransport_e;

typedef enum e1apCauseProtocol 
{
	E1apCauseProtocol_transfer_syntax_error	= 0,
	E1apCauseProtocol_abstract_syntax_error_reject = 1,
	E1apCauseProtocol_abstract_syntax_error_ignore_and_notify = 2,
	E1apCauseProtocol_message_not_compatible_with_receiver_state = 3,
	E1apCauseProtocol_semantic_error = 4,
	E1apCauseProtocol_abstract_syntax_error_falsely_constructed_message	= 5,
	E1apCauseProtocol_unspecified = 6
} E1apCauseProtocol_e;

typedef enum e1apCauseMisc 
{
	E1apCauseMisc_control_processing_overload = 0,
	E1apCauseMisc_not_enough_user_plane_processing_resources = 1,
	E1apCauseMisc_hardware_failure = 2,
	E1apCauseMisc_om_intervention = 3,
	E1apCauseMisc_unspecified = 4
} E1apCauseMisc_e;

typedef enum e1apCause_s
{
	RNL_UNSPECIFIED,
	RNL_CUCP_UE_E1AP_ID_ERROR,
	RNL_CUUP_UE_E1AP_ID_ERROR,
	RNL_PAIR_UE_E1AP_ID_ERROR,
	RNL_INTERACTIIN_WITH_OTHER_PROCEDURE,
	RNL_PDCP_COUNT_WRAP_ROUND,
	RNL_QCI_NOT_SUPPORT,
	RNL_5QI_NOT_SUPPORT,
	RNL_ENCRYPTION_ALGO_NOT_SUPPORT,
	RNL_INTEGRITY_ALGO_NOT_SUPPORT,
	RNL_UP_INTEGRITY_PROTECTION_NOT_POSSIBLE,
	RNL_UP_CONFIDENTIALITY_PROTECTION_NOT_POSSIBLE,
	RNL_MULTI_PDU_SESSION_ID_INSTANCE,
	RNL_UNKNOW_PDU_SESSION_ID,
	RNL_MULTI_QOS_FLOW_ID_INSTANCE,
	RNL_UNKNOW_QOS_FLOW_ID,
	RNL_MULTI_DRB_ID_INSTANCE,
	RNL_UNKNOW_DRB_ID,
	RNL_INVALID_QOS_COMBINATION,
	RNL_PROCEDURE_CANCELLED,
	RNL_NORMAL_RELEASE,
	RNL_NO_RADIO_RESOUCE_AVALABLE,
	RNL_ACTION_DESIRABLE_FOR_RADIO_REASONS,
	RNL_RESOUCE_NOT_AVALABLE_FOR_SLICE,
	RNL_PDCP_CONFIG_NOT_SUPPORT,
	RNL_CAUSE_MAX_VALUE,
	TLC_UNSPECIFIED,
	TLC_TRANSPORT_RESOURCE_UNAVALABLE,
	TLC_CAUSE_MAX_VALUE,
	PC_TRANSFER_SYNTAX_ERROR,
	PC_ABSTRACT_SYNTAX_ERROR_REJECT,
	PC_ABSTRACT_SYNTAX_ERROR_IGNORE_NOTIFY,
	PC_MSG_NOT_COMPATIBLE_WITH_STATE,
	PC_SMANITC_ERROR,
	PC_ABSTRACT_SYSNTAX_ERROR_FALSE_CONSTRUCT_MSG,
	PC_UNSPECIFIED,
	PC_CAUSE_MAX_VALUE,
	MISC_CONTROL_PROCESS_OVERLOAD,
	MISC_USER_PLANE_PROCESS_OVERLOAD,
	MISC_HARDWARE_FAILURE,
	MISC_OM_INTERVENTION,
	MISC_UNSPECIFIED,
	MISC_CAUSE_MAX_VALUE
}E1apCause_e;

typedef enum e1apProcCode 
{
	E1_e1reset								= 0,
	E1_e1errorIndication					= 1,
	E1_privateMessage						= 2,
	E1_gNB_CU_UP_E1Setup					= 3,
	E1_gNB_CU_CP_E1Setup					= 4,
	E1_gNB_CU_UP_ConfigurationUpdate		= 5,
	E1_gNB_CU_CP_ConfigurationUpdate		= 6,
	E1_e1Release							= 7,
	E1_bearerContextSetup					= 8,
	E1_bearerContextModification			= 9,
	E1_bearerContextModificationRequired	= 10,
	E1_bearerContextRelease					= 11,
	E1_bearerContextReleaseRequest			= 12,
	E1_bearerContextInactivityNotification	= 13,
	E1_dLDataNotification					= 14,
	E1_dataUsageReport						= 15,
	E1_gNB_CU_UP_CounterCheck				= 16,
	E1_gNB_CU_UP_StatusIndication			= 17,
	E1_uLDataNotification					= 18,
	E1_mRDC_DataUsageReport					= 19
} E1apProcCode_e;

typedef enum e1apProtocolIeId 
{
	E1ap_E1Cause										= 0,
	E1ap_E1CriticalityDiagnostics						= 1,
	E1ap_gNB_CU_CP_UE_E1AP_ID							= 2,
	E1ap_gNB_CU_UP_UE_E1AP_ID							= 3,
	E1ap_E1ResetType									= 4,
	E1ap_UE_associatedLogicalE1_ConnectionItem			= 5,
	E1ap_UE_associatedLogicalE1_ConnectionListResAck	= 6,
	E1ap_gNB_CU_UP_ID									= 7,
	E1ap_gNB_CU_UP_Name									= 8,
	E1ap_gNB_CU_CP_Name									= 9,
	E1ap_CNSupport										= 10,
	E1ap_SupportedPLMNs									= 11,
	E1ap_E1TimeToWait									= 12,
	E1ap_SecurityInformation							= 13,
	E1ap_UEDLAggregateMaximumBitRate					= 14,
	E1ap_System_BearerContextSetupRequest				= 15,
	E1ap_System_BearerContextSetupResponse				= 16,
	E1ap_BearerContextStatusChange						= 17,
	E1ap_System_BearerContextModificationRequest		= 18,
	E1ap_System_BearerContextModificationResponse		= 19,
	E1ap_System_BearerContextModificationConfirm		= 20,
	E1ap_System_BearerContextModificationRequired		= 21,
	E1ap_DRB_Status_List								= 22,
	E1ap_ActivityNotificationLevel						= 23,
	E1ap_ActivityInformation							= 24,
	E1ap_Data_Usage_Report_List							= 25,
	E1ap_New_UL_TNL_Information_Required				= 26,
	E1ap_GNB_CU_CP_TNLA_To_Add_List						= 27,
	E1ap_GNB_CU_CP_TNLA_To_Remove_List					= 28,
	E1ap_GNB_CU_CP_TNLA_To_Update_List					= 29,
	E1ap_GNB_CU_CP_TNLA_Setup_List						= 30,
	E1ap_GNB_CU_CP_TNLA_Failed_To_Setup_List			= 31,
	E1ap_DRB_To_Setup_List_EUTRAN						= 32,
	E1ap_DRB_To_Modify_List_EUTRAN						= 33,
	E1ap_DRB_To_Remove_List_EUTRAN						= 34,
	E1ap_DRB_Required_To_Modify_List_EUTRAN				= 35,
	E1ap_DRB_Required_To_Remove_List_EUTRAN				= 36,
	E1ap_DRB_Setup_List_EUTRAN							= 37,
	E1ap_DRB_Failed_List_EUTRAN							= 38,
	E1ap_DRB_Modified_List_EUTRAN						= 39,
	E1ap_DRB_Failed_To_Modify_List_EUTRAN				= 40,
	E1ap_DRB_Confirm_Modified_List_EUTRAN				= 41,
	E1ap_PDU_Session_Resource_To_Setup_List				= 42,
	E1ap_PDU_Session_Resource_To_Modify_List			= 43,
	E1ap_PDU_Session_Resource_To_Remove_List			= 44,
	E1ap_PDU_Session_Resource_Required_To_Modify_List	= 45,
	E1ap_PDU_Session_Resource_Setup_List				= 46,
	E1ap_PDU_Session_Resource_Failed_List				= 47,
	E1ap_PDU_Session_Resource_Modified_List				= 48,
	E1ap_PDU_Session_Resource_Failed_To_Modify_List		= 49,
	E1ap_PDU_Session_Resource_Confirm_Modified_List		= 50,
	E1ap_DRB_To_Setup_Mod_List_EUTRAN					= 51,
	E1ap_DRB_Setup_Mod_List_EUTRAN						= 52,
	E1ap_DRB_Failed_Mod_List_EUTRAN						= 53,
	E1ap_PDU_Session_Resource_Setup_Mod_List			= 54,
	E1ap_PDU_Session_Resource_Failed_Mod_List			= 55,
	E1ap_PDU_Session_Resource_To_Setup_Mod_List			= 56,
	E1ap_E1TransactionID								= 57,
	E1ap_Serving_PLMN									= 58,
	E1ap_UE_Inactivity_Timer							= 59,
	E1ap_System_GNB_CU_UP_CounterCheckRequest			= 60,
	E1ap_DRBs_Subject_To_Counter_Check_List_EUTRAN		= 61,
	E1ap_DRBs_Subject_To_Counter_Check_List_NG_RAN		= 62,
	E1ap_PPI											= 63,
	E1ap_gNB_CU_UP_Capacity								= 64,
	E1ap_GNB_CU_UP_OverloadInformation					= 65,
	E1ap_UEDLMaximumIntegrityProtectedDataRate			= 66,
	E1ap_PDU_Session_To_Notify_List						= 67,
	E1ap_PDU_Session_Resource_Data_Usage_List			= 68,
	E1ap_E1SNSSAI										= 69,
	E1ap_DataDiscardRequired							= 70
} E1apProtocolIeId_e;

typedef enum
{
	ACT_NOTI_DRB,
	ACT_NOTI_PDU_SESSION,
	ACT_NOTI_UE
} ActNotiLevel_e;

typedef enum
{
	BEARER_CXT_STATUS_CHANGE_SUSPEND,
	BEARER_CXT_STATUS_CHANGE_RESUME 
} BearCxtStatusChange_e;

typedef enum
{
	DATA_FORWARD_REQ_UL,
	DATA_FORWARD_REQ_DL,
	DATA_FORWARD_REQ_BOTH
} DataForwardReq_e;

typedef enum
{
	CipAlgorithm_NEA0,
	CipAlgorithm_NEA1,
	CipAlgorithm_NEA2,
	CipAlgorithm_NEA3
}CipAlgorithm_e;

typedef enum
{
	IpAlgorithm_NIA0,
	IpAlgorithm_NIA1,
	IpAlgorithm_NIA2,
	IpAlgorithm_NIA3
}IpAlgorithm_e;

typedef enum 
{
	PRIORITY_LEVEL_SPARE		= 0,
	PRIORITY_LEVEL_HIGHEST 		= 1,
	PRIORITY_LEVEL_LOWEST		= 14,
	PRIORITY_LEVEL_NO_PRIORITY 	= 15
} PriorityLevel_e;

typedef enum
{
	UL_CONFIG_NODATA	= 0,
	UL_CONFIG_SHARED	= 1,
	UL_CONFIG_ONLY		= 2
} UlConfig_e;

typedef enum
{
	DL_TX_STOP_STOP 	= 0,
	DL_TX_STOP_RESUME	= 1
} DlTXStop_e;
	
typedef enum
{
	RAT_TYPE_NR 		= 0,
	RAT_TYPE_EUTRA_NR	= 1,
	RAT_TYPE_RUTRA		= 2,
	RAT_TYPE_SPARE1 	= 3
} RatType_e;

typedef enum
{
	DEFAULT_DRB_TRUE,
	DEFAULT_DRB_FALSE
} DefaultDRB_e;

typedef enum
{
	SDAP_HEADER_PRESENT,
	SDAP_HEADER_ABSENT
} SdapHeader_e;

typedef enum
{
	PDCP_SN_SIZE_S12,
	PDCP_SN_SIZE_S18
} PdcpSNSize_e;

typedef enum
{
	RLCMODE_TM = 0,
	RLCMODE_AM = 1,
	RLCMODE_UM_BIDIRECTIONAL	= 2,
	RLCMODE_UM_UNIDIRECTIONAL_UL	= 3,
	RLCMODE_UM_UNIDIRECTIONAL_DL	= 4
} CuRlcMode_e;

typedef enum
{
	ROHC_PARA_PR_NOTHING, 
	ROHC_PARA_PR_ROHC,
	ROHC_PARA_PR_UL_ONLY_ROHC,
	ROHC_PARA_PR_CHOICE_ECTENSION
} RohcParaPR_e;

typedef enum
{
	ROHC_CONTINUE_ROHC_TRUE = 0
} RohcContinueRohc_e;

typedef enum
{
	T_REORFING_MS_0 = 0,
	T_REORFING_MS_1 = 1,
	T_REORFING_MS_2 = 2,
	T_REORFING_MS_4 = 3,
	T_REORFING_MS_5 = 4,
	T_REORFING_MS_8 = 5,
	T_REORFING_MS_10	= 6,
	T_REORFING_MS_15	= 7,
	T_REORFING_MS_20	= 8,
	T_REORFING_MS_30	= 9,
	T_REORFING_MS_40	= 10,
	T_REORFING_MS_50	= 11,
	T_REORFING_MS_60	= 12,
	T_REORFING_MS_80	= 13,
	T_REORFING_MS_100	= 14,
	T_REORFING_MS_120	= 15,
	T_REORFING_MS_140	= 16,
	T_REORFING_MS_160	= 17,
	T_REORFING_MS_180	= 18,
	T_REORFING_MS_200	= 19,
	T_REORFING_MS_220	= 20,
	T_REORFING_MS_240	= 21,
	T_REORFING_MS_260	= 22,
	T_REORFING_MS_280	= 23,
	T_REORFING_MS_300	= 24,
	T_REORFING_MS_500	= 25,
	T_REORFING_MS_750	= 26,
	T_REORFING_MS_1000 = 27,
	T_REORFING_MS_1250 = 28,
	T_REORFING_MS_1500 = 29,
	T_REORFING_MS_1750 = 30,
	T_REORFING_MS_2000 = 31,
	T_REORFING_MS_2250 = 32,
	T_REORFING_MS_2500 = 33,
	T_REORFING_MS_2750 = 34,
	T_REORFING_MS_3000 = 35,
	T_REORFING_INVALID = 0xFF
} TReordering_e;

typedef enum
{
	DISCARD_TIMER_MS_10 = 0,
	DISCARD_TIMER_MS_20 = 1,
	DISCARD_TIMER_MS_30 = 2,
	DISCARD_TIMER_MS_40 = 3,
	DISCARD_TIMER_MS_50 = 4,
	DISCARD_TIMER_MS_60 = 5,
	DISCARD_TIMER_MS_75 = 6,
	DISCARD_TIMER_MS_100	= 7,
	DISCARD_TIMER_MS_150	= 8,
	DISCARD_TIMER_MS_200	= 9,
	DISCARD_TIMER_MS_250	= 10,
	DISCARD_TIMER_MS_300	= 11,
	DISCARD_TIMER_MS_500	= 12,
	DISCARD_TIMER_MS_750	= 13,
	DISCARD_TIMER_MS_1500	= 14,
	DISCARD_TIMER_INFINITY	= 15,
	DISCARD_TIMER_INVALID = 0xFF
} DiscardTimer_e;

typedef enum
{
	UL_DATA_SPLIT_THRESHOLD_B0 = 0,
	UL_DATA_SPLIT_THRESHOLD_B100	= 1,
	UL_DATA_SPLIT_THRESHOLD_B200	= 2,
	UL_DATA_SPLIT_THRESHOLD_B400	= 3,
	UL_DATA_SPLIT_THRESHOLD_B800	= 4,
	UL_DATA_SPLIT_THRESHOLD_B1600	= 5,
	UL_DATA_SPLIT_THRESHOLD_B3200	= 6,
	UL_DATA_SPLIT_THRESHOLD_B6400	= 7,
	UL_DATA_SPLIT_THRESHOLD_B12800 = 8,
	UL_DATA_SPLIT_THRESHOLD_B25600 = 9,
	UL_DATA_SPLIT_THRESHOLD_B51200 = 10,
	UL_DATA_SPLIT_THRESHOLD_B102400 = 11,
	UL_DATA_SPLIT_THRESHOLD_B204800 = 12,
	UL_DATA_SPLIT_THRESHOLD_B409600 = 13,
	UL_DATA_SPLIT_THRESHOLD_B819200 = 14,
	UL_DATA_SPLIT_THRESHOLD_B1228800	= 15,
	UL_DATA_SPLIT_THRESHOLD_B1638400	= 16,
	UL_DATA_SPLIT_THRESHOLD_B2457600	= 17,
	UL_DATA_SPLIT_THRESHOLD_B3276800	= 18,
	UL_DATA_SPLIT_THRESHOLD_B4096000	= 19,
	UL_DATA_SPLIT_THRESHOLD_B4915200	= 20,
	UL_DATA_SPLIT_THRESHOLD_B5734400	= 21,
	UL_DATA_SPLIT_THRESHOLD_B6553600	= 22,
	UL_DATA_SPLIT_THRESHOLD_INFINITY	= 23
} UlDataSplitThreshold_e;

typedef enum
{
	PDCP_DUPLICATION_TRUE	= 0
} PdcpDuplication_e;

typedef enum
{
	PDCP_REESTABLISHMENT_TRUE	= 0
} PdcpReestablishment_e;

typedef enum
{
	PDCP_DATA_RECOVERY_TRUE = 0
} PdcpDataRecovery_e;

typedef enum
{
	DUPLICATION_ACTIVATION_ACTIVE	= 0,
	DUPLICATION_ACTIVATION_INACTIVE = 1
} DuplicationActivation_e;

typedef enum
{
	OUTOFORDER_DELIVERY_TRUE = 0
} OutOfOrderDelivery_e;

typedef enum pdcpSNStatusRequest 
{
	PDCP_SN_Status_Request = 0
} PdcpSNStatusRequest_e;

typedef enum newUlTnlInfoRequire 
{
	New_UL_TNL_Info_Required = 0
} NewUlTnlInfoRequire_e;

typedef enum dataDisRequire
{
	Data_Discard_Required = 0
}DataDisRequire_e;

typedef enum
{
	NG_DL_UP_UNCHANGED_TRUE = 0
}NgDlUpUnchange_e;

typedef enum
{
	EDI_ENABLE
}RDI_e;

#ifdef __cplusplus
}

#endif

#endif
