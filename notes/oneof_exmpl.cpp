
bool flag =
    ( (R_ABTYPE_ND == oldType || R_ABTYPE_SUBDIV == oldType || R_ABTYPE_SVIP == oldType || R_ABTYPE_BEAM == oldType ) &&
      R_ABTYPE_EMIT == m_bufSubDiv.ABON_TYPE)
    ||
    ( R_ABTYPE_EMIT == oldType &&
      (R_ABTYPE_ND == m_bufSubDiv.ABON_TYPE || R_ABTYPE_SUBDIV == oldType || R_ABTYPE_SVIP == m_bufSubDiv.ABON_TYPE || R_ABTYPE_BEAM == m_bufSubDiv.ABON_TYPE));


bool flag =
    ( oldType == oneof(R_ABTYPE_ND, R_ABTYPE_SUBDIV, R_ABTYPE_SVIP, R_ABTYPE_BEAM) &&
      R_ABTYPE_EMIT == m_bufSubDiv.ABON_TYPE)
    ||
    ( R_ABTYPE_EMIT == oldType &&
      m_bufSubDiv.ABON_TYPE == oneof(R_ABTYPE_ND, R_ABTYPE_SUBDIV, R_ABTYPE_SVIP, R_ABTYPE_BEAM));
