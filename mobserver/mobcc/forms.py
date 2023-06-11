from django import forms
from .models import Device, Command


class AddDeviceForm(forms.ModelForm):
    class Meta:
        model = Device
        fields = ('name', 'ip_address',)
        widgets = {
            'name': forms.TextInput(attrs={'id': 'device_name', 'class': 'form-control', 'placeholder': 'Device Name'}),
            'ip_address': forms.HiddenInput(),
        }


class SendCommandForm(forms.ModelForm):
    command = forms.CharField(max_length=255, widget=forms.TextInput(attrs={'class': "form-control"}))

    class Meta:
        model = Command
        fields = ('command',)
        widgets = {
            'command': forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Command'}),
        }

