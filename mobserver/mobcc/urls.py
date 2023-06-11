from django.urls import path
from . import views

urlpatterns = [
    path('', views.home_view, name='home'),
    path('add_device/', views.add_device_view, name='add_device'),
    path('send_command/<int:device_id>/', views.send_command_view, name='send_command'),
    path('commands_list/', views.commands_list, name='commands_list'),
]
