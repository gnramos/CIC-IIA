/** @file TimeUtils.h
 *
 * Definição de classes/funções auxiliares para manipulação de tempo na libIIA.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 12/05/2013 */

#ifndef IIA_UTILS_TIME_H
#define IIA_UTILS_TIME_H

// #include <stdint.h> // uint64_t
// #include <stdexcept>
#include <time.h>   // clock_gettime

namespace IIA {
namespace Utils {
/** Define o escopo para funções auxiliares de tempo. */
#ifndef __MACH__
/** Exige link para a <a href="http://linux.die.net/man/3/clock_gettime">biblioteca <i>rt</i></a>. */
#endif
namespace Time {
namespace {
    /** @cond DOXYGEN_SHOULD_SKIP_THIS */
	constexpr double THOUSAND = 1000;
	constexpr double MILLION = THOUSAND*THOUSAND;
	constexpr double BILLION = THOUSAND*MILLION;
	/** @endcond DOXYGEN_SHOULD_SKIP_THIS */
}

namespace {
/** Marca o instante de tempo no argumento dado. */
void get_cpu_time(timespec &time /**< variável para armazenar o tempo */) {
	//http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	time.tv_sec = mts.tv_sec;
	time.tv_nsec = mts.tv_nsec;
#else
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
#endif
	/*//High-resolution per-process timer from the CPU.
	if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time) != 0)
	    throw std::runtime_error("Unable to get clock time.");*/
}

/** Calcula o tempo passado entre os argumentos dados. */
timespec time_diff(const timespec &start_time, /**< tempo inicial */
				   const timespec &end_time    /**< tempo final */) {
	timespec diff;
	diff.tv_sec = end_time.tv_sec - start_time.tv_sec ;
	diff.tv_nsec = end_time.tv_nsec - start_time.tv_nsec;

	if(diff.tv_nsec < 0)
		diff.tv_sec -= 1, diff.tv_nsec += BILLION;

	return diff;
}

/** Converte o tempo dado em nanossegundos. */
double to_nano(const timespec &time) {return BILLION*time.tv_sec + time.tv_nsec;}

/** Converte o tempo dado em microssegundos. */
double to_micro(const timespec &time) {return to_nano(time)/THOUSAND;}

/** Converte o tempo dado em milissegundos. */
double to_mili(const timespec &time) {return to_micro(time)/THOUSAND;}

/** Converte o tempo dado em segundos. */
double to_sec(const timespec &time) {return to_mili(time)/THOUSAND;}

/** Converte o tempo dado em minutos. */
double to_min(const timespec &time) {return to_sec(time)/60;}
} // unnamed namespace
} // namespace Time
} // namespace Utils
} // namespace IIA

#endif	/* IIA_UTILS_TIME_H */
