from django.db import models

# Create your models here.

class Metrics(models.Model):
    datetime = models.DateTimeField(auto_now_add = True, blank = False)
    temperature = models.IntegerField()
    humidity = models.IntegerField()
    pressure = models.IntegerField()
