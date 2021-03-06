from nipype.interfaces.base import CommandLine, CommandLineInputSpec, TraitedSpec, File, Directory, traits, isdefined, InputMultiPath, OutputMultiPath
import os

class GradientAnisotropicDiffusionImageFilterInputSpec(CommandLineInputSpec):
    inputVolume = File( exists = True,argstr = "--inputVolume %s")
    numberOfIterations = traits.Int( argstr = "--numberOfIterations %d")
    timeStep = traits.Float( argstr = "--timeStep %f")
    conductance = traits.Float( argstr = "--conductance %f")
    outputVolume = traits.Either(traits.Bool, File(), hash_files = False,argstr = "--outputVolume %s")


class GradientAnisotropicDiffusionImageFilterOutputSpec(TraitedSpec):
    outputVolume = File( exists = True)


class GradientAnisotropicDiffusionImageFilter(CommandLine):

    input_spec = GradientAnisotropicDiffusionImageFilterInputSpec
    output_spec = GradientAnisotropicDiffusionImageFilterOutputSpec
    _cmd = " GradientAnisotropicDiffusionImageFilter "
    _outputs_filenames = {'outputVolume':'outputVolume.nii'}

    def _list_outputs(self):
        outputs = self.output_spec().get()
        for name in outputs.keys():
            coresponding_input = getattr(self.inputs, name)
            if isdefined(coresponding_input):
                if isinstance(coresponding_input, bool) and coresponding_input == True:
                    outputs[name] = os.path.abspath(self._outputs_filenames[name])
                else:
                    if isinstance(coresponding_input, list):
                        outputs[name] = [os.path.abspath(inp) for inp in coresponding_input]
                    else:
                        outputs[name] = os.path.abspath(coresponding_input)
        return outputs

    def _format_arg(self, name, spec, value):
        if name in self._outputs_filenames.keys():
            if isinstance(value, bool):
                if value == True:
                    value = os.path.abspath(self._outputs_filenames[name])
                else:
                    return ""
        return super(GradientAnisotropicDiffusionImageFilter, self)._format_arg(name, spec, value)

