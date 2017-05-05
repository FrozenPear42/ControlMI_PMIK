from __future__ import with_statement
import Live
import time  # We will be using time functions for time-stamping our log file outputs

from _Framework.ButtonElement import ButtonElement
from _Framework.ButtonMatrixElement import ButtonMatrixElement
from _Framework.ChannelStripComponent import *
from _Framework.EncoderElement import EncoderElement
from _Framework.ClipSlotComponent import ClipSlotComponent
from _Framework.CompoundComponent import  CompoundComponent
from _Framework.ControlElement import ControlElement
from _Framework.ControlSurface import ControlSurface
from _Framework.ControlSurfaceComponent import ControlSurfaceComponent
from _Framework.InputControlElement import *
from _Framework.MixerComponent import MixerComponent
from _Framework.SceneComponent import SceneComponent
from _Framework.SessionComponent import SessionComponent
from _Framework.SliderElement import SliderElement
from _Framework.TransportComponent import TransportComponent
from _Framework.DeviceComponent import DeviceComponent

from consts import *


class ControlMI(ControlSurface):
    __module__ = __name__
    __doc__ = " ControlMI controller script"

    def __init__(self, c_instance):
        ControlSurface.__init__(self, c_instance)
        self._suppress_session_highlight = True
        self._suppress_send_midi = True  # Turn off rebuild MIDI map until after we're done setting up
        self.log("--------------= ControlMI log opened =--------------")
        with self.component_guard():
            # OBJECTS
            self.session = None
            self.mixer = None
            self.view = None
            self.device = None
            self.transport = None
            # INITIALIZE MIXER, SESSIONS
            self._setup_session_control()  # Setup the session object
            self._setup_mixer_control()  # Setup the mixer object
            self.session.set_mixer(self.mixer)  # Bind mixer to session
            self._setup_device_control()  # Setup the device object
            self._setup_transport_control()  # Setup transport object
            self._set_initial_mode()
            self.set_device_component(self.device)  # Bind device to control surface-
            self.set_highlighting_session_component(self.session)

            for component in self.components:
                component.set_enabled(True)

        self._suppress_session_highlight = True
        self._suppress_send_midi = True  # Turn rebuild back on, once we're done setting up

    def _setup_session_control(self):
        self.show_message("#################### SESSION: ON ##############################")
        self.session = SessionComponent(num_tracks, num_scenes)
        self.session.set_offsets(0, 0)
        self.session.set_track_bank_buttons(ButtonElement(False, MIDI_CC_TYPE, data_channel, session_right),
                                            ButtonElement(False, MIDI_CC_TYPE, data_channel, session_left))

    def _setup_mixer_control(self):
        self.mixer = MixerComponent(num_tracks, 0, False, False)
        self.mixer.name = 'Mixer'
        self.mixer.set_track_offset(0)

    def _setup_device_control(self):
        self.device = DeviceComponent()
        self.device.name = 'Device_Component'

    def _setup_transport_control(self):
        self.transport = TransportComponent(self)

    def _clear_controls(self):
        self.mixer._set_send_nav(None, None)
        for track_index in range(num_tracks):
            strip = self.mixer.channel_strip(track_index)
            strip.set_solo_button(None)
            strip.set_mute_button(None)
            strip.set_arm_button(None)
            strip.set_select_button(None)
        # TRANSPORT
        self.transport.set_stop_button(None)
        self.transport.set_play_button(None)
        self.transport.set_record_button(None)

        self.log_message("Controls Cleared")

    def _set_initial_mode(self):
        is_momentary = True
        ### MIXER

        for index in range(num_tracks):
            strip = self.mixer.channel_strip(index)
            strip.name = 'Mixer_ChannelStrip_' + str(index)
            strip.set_volume_control(SliderElement(MIDI_CC_TYPE, data_channel, mixer_volume_cc[index]))
            strip._invert_mute_feedback = True

        self.mixer.master_strip().set_volume_control(SliderElement(MIDI_CC_TYPE, data_channel, mixer_master_cc))
        self.transport.set_stop_button(ButtonElement(is_momentary, MIDI_CC_TYPE, data_channel, transport_stop_cc))
        self.transport.set_play_button(ButtonElement(not is_momentary, MIDI_CC_TYPE, data_channel, transport_play_cc))
        self.transport.set_record_button(ButtonElement(is_momentary, MIDI_CC_TYPE, data_channel, transport_record_cc))

    def disconnect(self):
        """clean things up on disconnect"""
        self.log("--------------= ControlMI log closed =--------------")
        self._clear_controls()
        self.session = None
        self.mixer = None
        self.view = None
        self.device = None
        self.transport = None

        self.set_device_component(None)
        ControlSurface.disconnect(self)
        return None

    def log(self, message):
        self.log_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + message)
