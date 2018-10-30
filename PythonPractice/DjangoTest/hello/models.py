from django.db import models


# Create your models here.
class Number(models.Model):
    value1 = models.IntegerField(default=0)
    value2 = models.IntegerField(default=0)
    value3 = models.IntegerField(default=0)
