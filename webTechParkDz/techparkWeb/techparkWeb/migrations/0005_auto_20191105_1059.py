# Generated by Django 2.2.6 on 2019-11-05 10:59

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('webApp', '0004_auto_20191105_0934'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='author',
            options={'managed': True, 'verbose_name': 'Author', 'verbose_name_plural': 'Author'},
        ),
        migrations.RemoveField(
            model_name='post',
            name='tag',
        ),
        migrations.AddField(
            model_name='post',
            name='tag',
            field=models.ManyToManyField(blank=True, null=True, to='webApp.tag'),
        ),
    ]
