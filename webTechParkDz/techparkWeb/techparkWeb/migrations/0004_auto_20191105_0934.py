# Generated by Django 2.2.6 on 2019-11-05 09:34

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('webApp', '0003_auto_20191105_0819'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='author',
            options={'managed': True, 'verbose_name': 'Author', 'verbose_name_plural': 'Autor'},
        ),
        migrations.AlterModelTable(
            name='author',
            table='',
        ),
    ]