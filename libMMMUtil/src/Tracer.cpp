#include "Tracer.h"

Tracer* Tracer::sm_singleton = NULL;
Tracer::ELogLevel Tracer::sm_traceThreshold = Tracer::ELogLevel::TRACE;
/**
 * @name Self - Return the trace singleton
 * @return Tracer* trace singleton
 */
 Tracer::ELogSystem Tracer::sm_traceSystem = (Tracer::ELogSystem) 255;
Tracer* Tracer::Self()
{
  return sm_singleton;
}
/**
 * @name Tracer - Singleton constructor for the Tracer instance
 * @return Tracer
 */
Tracer::Tracer()
{
  if(sm_singleton == NULL)
    sm_singleton = this;
}
/**
 * @name SetTraceLevel - Set the highest trace level that will be written to the
 *                       log.  All higher level traces are discarded
 * @param traceLevel -  Tracing level as defined by ELogLevel 
 * @param traceSystem -  Used to identify the source of the trace
 * @return void
 */
void Tracer::SetTraceThreshold(ELogLevel traceLevel, ELogSystem traceSystem)
{
  sm_traceThreshold = traceLevel;
  sm_traceSystem = traceSystem;
}
