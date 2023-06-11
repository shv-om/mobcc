from django.shortcuts import render, redirect, get_object_or_404
from django.http import JsonResponse, HttpResponse, HttpResponseRedirect
import socket
import json
from django.views.decorators.csrf import csrf_exempt
from .models import Device, Command
from .forms import AddDeviceForm, SendCommandForm
import requests


def get_client_ip(request):
    x_forwarded_for = request.META.get('HTTP_X_FORWARDED_FOR')
    if x_forwarded_for:
        ip = x_forwarded_for.split(',')[0]
    else:
        ip = request.META.get('REMOTE_ADDR')
    return ip

@csrf_exempt
def add_device_view(request):
    if request.method == 'POST':
        form = AddDeviceForm(request.POST)
        if form.is_valid():
            device = form.save(commit=False)
            device.ip_address = get_client_ip(request)
            device.save()
            return redirect('home')
    else:
        form = AddDeviceForm()
    context = {'form': form}
    return render(request, 'add_device.html', context)


def commands_list(request):
    commands = Command.objects.all()
    return render(request, 'command_list.html', {'commands': commands})


def home_view(request):
    devices = Device.objects.all()
    if request.method == 'POST':
        device_id = request.POST.get('device')
        return redirect('send_command', device_id=device_id)
    context = {
        'devices': devices,
    }
    return render(request, 'home.html', context)


def send_command_view(request, device_id):
    device = get_object_or_404(Device, id=device_id)
    if request.method == 'POST':
        form = SendCommandForm(request.POST)
        if form.is_valid():
            command = form.cleaned_data['command']
            print(command, device)
            try:
            	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                    s.connect((device.ip_address, 1234))
                    s.sendall(command.encode())
                    response = s.recv(1024).decode()
                    print(response)
                    # Save the command and response to the database
                    Command.objects.create(device=device, command=command, response=response)
                    # return response

            except Exception as e:
            	response = str(e)
            
            return HttpResponse(response)

    else:
        form = SendCommandForm()
        return render(request, 'send_commands.html', {'form': form, 'device': device})


# import socket

# def send_socket_command(ip_address, port, command):
#     with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#         s.connect((ip_address, port))
#         s.sendall(command.encode())
#         response = s.recv(1024).decode()
#         return response


# def send_command(request):
#     if request.method == 'POST':
#         form = CommandForm(request.POST)
#         if form.is_valid():
#             command = form.cleaned_data['command']
#             device_id = form.cleaned_data['device']
#             device = Device.objects.get(id=device_id)
#             ip_address = device.ip_address
#             port = device.port
#             response = send_socket_command(ip_address, port, command)
#             return render(request, 'result.html', {'response': response})
#     else:
#         form = CommandForm()
#         devices = Device.objects.all()
#         return render(request, 'send_command.html', {'form': form, 'devices': devices})



