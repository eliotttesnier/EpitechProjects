using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class door : MonoBehaviour
{
    public AudioSource sound;
    public bool division;
    public bool multiplication;
    public float value;

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player") {
            Destroy(gameObject);
            player Player = FindObjectOfType<player>();
            if (multiplication == true)
                Player.jav_size = Player.jav_size * (value);
            if (division == true)
                Player.jav_size = Player.jav_size / (value);
            if (!multiplication & !division)
                Player.jav_size += (value / 10);
            sound.Play(0);
        }
    }
}
