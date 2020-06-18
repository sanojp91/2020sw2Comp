# 2020sw2Comp
## Compressor plugin for Music Software Development 2

![alt text](https://github.com/sanojp91/2020sw2Comp/blob/master/PluginCoverPage.png?raw=true "SatComp")

SatComp is a compressor with a built-in saturation circuit that can add anything from gentle saturation to full on distortion to the signal. 
It can be very handy to use when parallel compressing due to the wet/dry mix knob that blends the compressed and saturated signal with the unaffected clean signal.

The default signal flow of the plugin is:
Input Signal -> Input Gain -> Threshold -> Hard/Soft Knee -> Attack Time (MS) -> Release time (MS) -> Saturation/Distortion -> Makeup Gain -> Output Signal

This mode first compresses the signal, then apply saturation/distortion to add more grit to the signal.

This signal flow can be switched using the “Pre/Post” toggle switch to put the saturation/distortion circuit before the compression stage. 
This mode saturates the signal and then compresses it to give a slightly different flavour on the transients. 

The is a bypass toggle switch that lets the signal go through unaffected by either compression or saturation,
as well as a Mix knob that lets the user decide how much of the affected signal should be present in the circuit, this makes it easy to use for parallel compression. 

![alt text](https://github.com/sanojp91/2020sw2Comp/blob/master/PluginParameters.png?raw=true "SatComp Parameters")
