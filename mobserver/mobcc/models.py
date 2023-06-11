from django.db import models

class Device(models.Model):
    name = models.CharField(max_length=100)
    ip_address = models.CharField(max_length=100, blank=True, null=True)
    last_seen = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.name

class Command(models.Model):
    device = models.ForeignKey(Device, on_delete=models.CASCADE)
    command = models.CharField(max_length=255)
    response = models.TextField(blank=True, null=True)
