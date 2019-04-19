from NuRadioMC.SignalGen.askaryan import get_time_trace
from NuRadioMC.utilities import units, fft
import numpy as np
import matplotlib.pyplot as plt

E = 1e20 * units.eV
n_index = 1.78
theta = np.arccos(1. / n_index)

dt = 0.01 * units.ns
n_samples = 2048
ff = np.fft.rfftfreq(n_samples, dt)
tt = np.arange(0, n_samples * dt, dt)
R = 1 * units.km

model = 'Alvarez2000'
shower_type = 'EM'

domega = 0.1 * units.deg
trace_1 = get_time_trace(E, theta+domega, n_samples, dt, shower_type, n_index, R, model)
domega = 0.3 * units.deg
trace_2 = get_time_trace(E, theta+domega, n_samples, dt, shower_type, n_index, R, model)
spectrum_1= fft.time2freq(trace_1)
spectrum_2= fft.time2freq(trace_2)
spectrum_1 *= 1. / units.V * units.MHz * dt
spectrum_2 *= 1. / units.V * units.MHz * dt
freqs = np.fft.rfftfreq(n_samples, dt)

fig = plt.figure(figsize=(10,5))
ax1 = fig.add_subplot(121)
ax1.plot(tt, trace_1, color='black', label='$\\theta_C+0.1\degree$', linestyle='-', linewidth=2)
ax1.plot(tt, trace_2, color='red', label='$\\theta_C+0.3\degree$', linestyle='--', linewidth=2)
ax1.set_xlabel('Time (ns)')
ax1.set_ylabel('Voltage (V)')
ax1.set_xlim(5,15)
ax1.legend()

ax2 = fig.add_subplot(122)
ax2.plot(freqs, np.abs(spectrum_1), color='black', label='something', linestyle='-', linewidth=2)
ax2.plot(freqs, np.abs(spectrum_2), color='red', label='something', linestyle='--', linewidth=2)
ax2.set_ylabel('Spectrum (V/MHz)')
ax2.set_xlabel('Frequency (GHz)')
ax2.set_yscale("log")
ax2.set_xscale("log")
ax2.set_xlim(50e-3,3)
ax2.set_ylim(1e-4,1e-2)
plt.tight_layout()
fig.savefig("askaryan.png")
