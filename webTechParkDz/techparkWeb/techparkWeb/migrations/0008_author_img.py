# Generated by Django 2.2.6 on 2019-11-05 13:04

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('webApp', '0007_auto_20191105_1237'),
    ]

    operations = [
        migrations.AddField(
            model_name='author',
            name='img',
            field=models.TextField(default='https://picsum.photos/200/200', max_length=200),
        ),
    ]