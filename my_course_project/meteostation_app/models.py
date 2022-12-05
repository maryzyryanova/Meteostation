from django.db import models

# Create your models here.

class Metrics(models.Model):
    datetime = models.DateTimeField(auto_now = True, blank = False)
    temperature = models.FloatField()
    humidity = models.FloatField()
    pressure = models.FloatField()
